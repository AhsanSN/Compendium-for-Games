const db = require('electron-db');
const electron = require('electron');

const app = electron.app || electron.remote.app;

function createTable() {
    db.createTable('games', (succ, msg) => {
        // succ - boolean, tells if the call is successful
        console.log("Success: " + succ);
        console.log("Message: " + msg);
    })
}

function insert() {
    let obj = new Object();

    obj.name = "Alexius Academia";
    obj.address = "Paco, Botolan, Zambales";

    db.insertTableContent('games', obj, (succ, msg) => {
        // succ - boolean, tells if the call is successful
        console.log("Success: " + succ);
        console.log("Message: " + msg);
    })
}

function getRows() {
    db.getAll('games', (succ, data));
    // {
    //     // succ - boolean, tells if the call is successful
    //     // data - array of objects that represents the rows.
    // }
}

function getParticRow() {
    db.getRows('games', {
        address: "Paco, Botolan, Zambales",
        name: 'Alexius Academia'
    }, (succ, result) => {
        // succ - boolean, tells if the call is successful
        console.log("Success: " + succ);
        console.log(result);
    })
}

//exporting
module.exports.createTable = createTable
module.exports.insert = insert
module.exports.getRows = getRows
module.exports.getParticRow = getParticRow

