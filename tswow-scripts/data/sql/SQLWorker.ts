
const { parentPort, workerData } = require('worker_threads');
const mysql = require('mysql2'); 

async function runQueries() {
    let connection = mysql.createConnection(workerData.db);
    try {
        for (let i = 0; i < workerData.queryInfo.length; i++) {
            let queryInfo = workerData.queryInfo[i];

            if (queryInfo.type === 'query') {
                await new Promise<void>((resolve, reject) => {
                    connection.query(queryInfo.query, (err) => {
                        if (err) {
                            console.log(err);
                            parentPort.postMessage({ err: err });
                            reject(err);
                        } else {
                            resolve();
                        }
                    });
                });
            } else if (queryInfo.type === 'exec') {
                await new Promise<void>((resolve, reject) => {
                    connection.execute(queryInfo.query, queryInfo.values, (err) => {
                        if (err) {
                            console.log(err);
                            parentPort.postMessage({ err: err });
                            reject(err);
                        } else {
                            resolve();
                        }
                    });
                });
            }
        }
    } catch (e) {
        console.log(e);
        parentPort.postMessage({ err: e });
    } finally {
        connection.end();
        parentPort.postMessage({ final: true });
    }
}

runQueries();