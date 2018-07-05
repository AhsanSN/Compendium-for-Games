const db = require('electron-db');
const electron = require('electron');
const exec = require('child_process').execFile;
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
    db.getAll('games', (succ, data) => {
        console.log(succ)
        console.log(data)
    }) 
        // succ - boolean, tells if the call is successful
    // data - array of objects that represents the rows.
    
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

var fun =function(){
   console.log("fun() start");
   exec('myexe.exe', function(err, data) {  
        console.log(err)
        console.log(data.toString());                       
    });  
}
fun();

//exporting
module.exports.createTable = createTable
module.exports.insert = insert
module.exports.getRows = getRows
module.exports.getParticRow = getParticRow

