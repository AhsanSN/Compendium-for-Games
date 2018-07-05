//game Details
var gameName = "none";
var gameAbout = "none"
var gameExe = "none";
//using ipc to openwindow
const electron = require('electron');
const db = require('../database.js');
const { ipcRenderer } = require('electron');

ipcRenderer.on('asynchronous-reply', (event, arg) => {
    console.log(arg) // received exe path
    gameExe = arg;
});

function openDialog() {
    ipcRenderer.send('asynchronous-message', 'ping');
}

function uploadGame() {
    //console.log()
    console.log(gameAbout)
    console.log(gameExe)
    console.log(gameName)
    gameName = document.getElementById("username").innerHTML;
    gameAbout = document.getElementById("about").innerHTML;
    if (((gameName != "") && (gameExe != "none") && (gameAbout != ""))) {
        //ready for upload
        db.insert(gameName, gameAbout, gameExe);
    }
}