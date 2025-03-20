
const { parentPort, workerData } = require('worker_threads');
const mysql = require('mysql2');

async function runQueries() {
    const connection = mysql.createConnection(workerData.db);
    try {
        for (const queryInfo of workerData.queryInfo) {
            await new Promise<void>((resolve, reject) => {
                if (queryInfo.isQuery)
                    connection.query(queryInfo.query, (err) => cb(err, resolve, reject));
                else
                    connection.execute(queryInfo.query, queryInfo.values, (err) => cb(err, resolve, reject));

            });
        }
    } catch (e) {
        console.error(e);
        parentPort.postMessage({ err: e });
    } finally {
        connection.end();
        parentPort.postMessage({ final: true });
    }
}

function cb(err: any, resolve, reject) {
    if (err) {
        console.error(err);
        parentPort.postMessage({ err });
        reject(err);
    } else {
        resolve();
    }
};

runQueries();