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
import * as path from 'path';
import { DBCRow } from '../../data/dbc/DBCRow';
import { dataset } from '../../data/Settings';
import { SDBCGenerator } from './SDBCGenerator';
import { DBCFile } from '../../data/dbc/DBCFile';

export class SDBCFile<C, Q, R extends DBCRow<C, Q>> extends DBCFile<C, Q, R> {
    protected override defaultPath() {
        return path.join(dataset.dbc_source.get(), this.name + '.sdbc');
    }

    protected override load(filePath: string = this.defaultPath()) {
        if (!this.loaded) {
            if (!fs.existsSync(filePath))
                new SDBCGenerator(this.getDefaultRows()).generate(this.getPath());
            this.buffer.read(filePath);
            this.loaded = true;
        }
    }

    getDefaultRows() { return [] }//override for any work required for default data

    fileWork() { }//override for any work required just before saving dbc

    getPath() { return this.defaultPath(); }

    static initialize(file: SDBCFile<any, any, any>, rowSize: number) {
        file.loaded = true;
        file.buffer.initialize(rowSize)
    }
}
