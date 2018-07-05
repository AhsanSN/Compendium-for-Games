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
    if ((gameName && gameExe && gameAbout) != "none") {
        gameName = document.getElementById("username");
        gameAbout = document.getElementById("about");
        //ready for upload
        db.insert(gameName, gameAbout, arg);
    }
}