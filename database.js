const electron = require('electron');
const exec = require('child_process').execFile;
const app = electron.app || electron.remote.app;
const fs = require('fs');
var stream = fs.createWriteStream("gamesDB.txt", { flags: 'a' });
const { ipcMain } = require('electron')


function insert(gameName, aboutGame,exePath) {
    stream.write(gameName + '\n');
    stream.write(aboutGame + '\n');
    stream.write(exePath + '\n');
    console.log("game added to file");
}

function getRows(callback) {
    var fileResult;
    fs.readFile('gamesDB.txt', function (error, data) {
        if (error)
            callback(error, null);
        else {
            fileResult = data.toString().split("\n");
            callback(null, fileResult);
        }
    });
}

function getArrayGName(fullArray){
    var arrayName = [];
    for (var i = 0; i < fullArray.length; i++) {
        if (i%3 == 0){
            arrayName.push(fullArray[i]);
        }
    }
    return arrayName;
}

function getArrayGAbout(fullArray){
    var arrayAbout = [];
    for (var i = 0; i < fullArray.length; i++) {
        if (((i-1)%3) == 0){
            arrayAbout.push(fullArray[i]);
        }
    }
    return arrayAbout;
}

function getArrayGExe(fullArray){
    var arrayExe = [];
    for (var i = 0; i < fullArray.length; i++) {
        if (((i-2)%3) == 0){
            arrayExe.push(fullArray[i]);
        }
    }
    return arrayExe;
}

function runExe(exe = "myexe.exe") {
    console.log("running exe" + exe);
    exec(exe, function(err, data) {  
        console.log(err)
        console.log(data.toString());                       
    });
}

app.on('ready', function () {
    console.log("ready")
    ipcMain.on('runGame', (event, arg) => {
        console.log("received game signal")
    })
});



//exporting
module.exports.insert = insert
module.exports.getRows = getRows
module.exports.runExe = runExe
module.exports.getArrayGName = getArrayGName
module.exports.getArrayGAbout = getArrayGAbout
module.exports.getArrayGExe = getArrayGExe
