/*
 * This file is part of tswow (https://github.com/tswow)
 *
 * Copyright (C) 2020 tswow <https://github.com/tswow/>
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
import * as fs from 'fs';
import * as mysql from 'mysql2';
import { queryToSql } from '../query/Query';
import { BuildArgs, datasetName, NodeConfig } from '../Settings';
import { SqlRow } from './SQLRow';
import { SqlTable } from './SQLTable';
import { translate } from './SQLTranslate';
import deasync = require('deasync');
const { Worker } = require('worker_threads');

export class PreparedStatement {
    private asyncStatement: any;

    readonly query: string;
    private early: any[][] = []
    private normal: any[][] = []
    private late: any[][] = []

    constructor(statement: string) {
        this.query = statement;
    }

    writeEarly(values: any[]) {
        this.early.push(values);
    }

    writeNormal(values: any[]) {
        this.normal.push(values);
    }

    writeLate(values: any[]) {
        this.late.push(values);
    }

    static clear(stmnt: PreparedStatement) {
        stmnt.early = []
        stmnt.normal = []
        stmnt.late = []
    }

    static setStatement(stmnt: PreparedStatement, asyncStatement: any) {
        stmnt.asyncStatement = asyncStatement;
    }

    static getStatement(stmnt: PreparedStatement) {
        return stmnt.asyncStatement;
    }
}

export class Connection {
    static end(connection: Connection) {
        if (connection.sync !== undefined) {
            connection.sync.end();
            connection.sync = undefined;
        }

        if (connection.async !== undefined) {
            connection.async.end();
            connection.async = undefined;
        }
    }

    static connect(connection: Connection) {
        this.end(connection);
        if (NodeConfig.UsePooling) {
            let s = Object.assign({}, connection.settings, { enableKeepAlive: true })
            connection.async = mysql.createPool(s);
            connection.sync = mysql.createPool(s);
        } else {
            connection.async = mysql.createConnection(connection.settings);
            connection.sync = mysql.createConnection(connection.settings);
            connection.async.connect((err) => {
                if (!err) return;
                console.error(`Failed to connect with settings`, connection.settings, err)
                process.exit(-1);
            });
            connection.sync.connect((err) => {
                if (!err) return;
                console.error(`Failed to connect with settings`, connection.settings, err)
                process.exit(-1);
            });
        }

        connection.syncQuery = deasync(connection.sync.query.bind(connection.sync));
    }

    protected settings: any;
    protected async: mysql.Pool | mysql.Connection | undefined;
    protected sync: mysql.Pool | mysql.Connection | undefined;
    protected syncQuery: any;

    constructor(obj: any) {
        this.settings = obj;
        this.settings.dateStrings = true;
        this.settings.multipleStatements = true;
    }

    protected statements: PreparedStatement[] = []
    protected early: string[] = [];
    protected normal: string[] = [];
    protected late: string[] = [];
    protected workerCount = 50

    databaseName() {
        return this.settings.database;
    }

    read(query: string) {
        if (this.sync === undefined) {
            throw new Error(
                `Tried to read from a disconnected adapter.\n`
                + `This typically indicates that your node_modules folder is corrupt. Try deleting it, re-run 'npm i' and restart TSWoW.\n`
                + `\n`
                + `If the problem persists, please report this as a bug.`
            );
        }
        SqlConnection.log(this.settings.database, query);
        return this.syncQuery(query);
    }

    prepare(statement: string) {
        let prep = new PreparedStatement(statement);
        this.statements.push(prep);
        return prep;
    }

    write(query: string) {
        this.normal.push(query);
    }

    writeEarly(query: string) {
        this.early.push(query);
    }

    writeLate(query: string) {
        this.late.push(query);
    }

    async apply() {
        const doPriority = async (name) => {
            const queries: any[][] = [];
            for (let i = 0; i < this.workerCount; i++)
                queries.push([])

            let count = 0;
            for (let i = 0; i < this[name].length; i++) {
                queries[count % this.workerCount].push({ type: 'query', query: this[name][i] });
                count++
            }
            for (let i = 0; i < this.statements.length; i++) {
                const statement = this.statements[i];
                for (let j = 0; j < statement[name].length; j++) {
                    const values = statement[name][j];
                    queries[count % this.workerCount].push({ type: 'exec', query: statement.query, values: values });
                    count++
                }
            }

            let promises = []
            for (let i = 0; i < queries.length; i++) {
                if (queries[i].length > 0)
                    promises.push(
                        new Promise<void>((res, rej) => {
                            new Worker("./bin/scripts/wow/data/sql/SQLWorker.js", {
                                workerData: { queryInfo: queries[i], db: this.settings }
                            }).on('message', (message) => {
                                if (message.err) {
                                    console.log(message.err)
                                }
                                if (message.final)
                                    res()
                            })
                        }));
            }
            return Promise.all(promises);
        };

        await doPriority('early');
        await doPriority('normal');
        await doPriority('late');
        this.statements.forEach(x => PreparedStatement.clear(x))
        this.early = [];
        this.normal = [];
        this.late = [];
    }
}

/**
 * Represents the global SQL connection.
 *
 * @motivation Since we already decided not to allow parallell patching, this might
 * just as well be static so we avoid having to pass around a script context to all
 * data structures. Can always change if we want to support paralellism later.
 */
export class SqlConnection {
    static additional: Connection[] = [];
    static logFile: number;
    static log(db: string, sql: string) {
        if (BuildArgs.LOG_SQL) {
            fs.writeSync(this.logFile, `[${db}]: ${sql}\n`);
        }
    }

    static auth = new Connection(NodeConfig.DatabaseSettings('auth'));
    static characters = new Connection(NodeConfig.DatabaseSettings('characters', 'default.realm'));
    static world_dst = new Connection(NodeConfig.DatabaseSettings('world', datasetName));
    static world_src = new Connection(NodeConfig.DatabaseSettings('world_source', datasetName))

    private static query_cache: { [table: string]: { [query: string]: boolean } } = {}

    protected static endConnection() {
        Connection.end(this.auth);
        Connection.end(this.characters);
        Connection.end(this.world_src);
        Connection.end(this.world_dst);
        this.additional.forEach(x => Connection.end(x));
        this.additional = [];
    }

    static connect() {
        this.endConnection();
        [this.auth, this.world_dst, this.world_src, this.characters]
            .forEach((x) => Connection.connect(x));
    }

    static getRows<C, Q, T extends SqlRow<C, Q>>(table: SqlTable<C, Q, T>, where: Q, first: boolean) {
        const whereSql = queryToSql(where, false);
        const whereLookup = whereSql + first;

        // Check cache for the query, don't repeat
        let tableCache = this.query_cache[table.name] || (this.query_cache[table.name] = {});
        if (tableCache[whereLookup]) {
            return [];
        }
        tableCache[whereLookup] = true;

        const sqlStr = `SELECT * FROM ${table.name} ${whereSql.length > 1 ? ` WHERE ${whereSql}` : ''} ${first ? 'LIMIT 1' : ''};`;
        const res = SqlConnection.querySource(sqlStr);
        const rowsOut: T[] = [];
        for (const row of res) {
            translate(table.name, row, 'IN');
            const jsrow = SqlTable.createRow(table, row);
            rowsOut.push(jsrow);
        }
        return rowsOut;
    }

    static querySource(sql: string): any {
        return this.world_src.read(sql);
    }

    static allDbs() {
        return this.additional.concat([this.world_src, this.world_dst, this.auth, this.characters]);
    }
}
