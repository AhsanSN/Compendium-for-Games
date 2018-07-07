//game Details
var gameName = "none";
var gameAbout = "none"
var gameExe = "none";
//using ipc to openwindow
const electron = require('electron');
const fs = require('fs');
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
    gameName = document.getElementById("username").value;
    gameAbout = document.getElementById("about").value;
    console.log(gameAbout)
    console.log(gameExe)
    console.log(gameName)
    if (((gameName != "") && (gameExe != "none") && (gameAbout != ""))) {
        //ready for upload
        console.log("ready for upload")
        //chaning file name
        db.getRows(function (err, data) {
            if (err) {
                console.log("ERROR : ", err);
            } else {
                var nGames = (data.length-1) / 3
                console.log("nGames = " + nGames)
                var newGameExe = "../game" + (nGames + 1)
                console.log(newGameExe)
                document.getElementById("form").innerHTML = "<p>Your game has been successfully uploaded to this software's local storage.</p> <h5> <a href='home.html'> Return to main menu</a></h5>";
                //transfer file to /games/ and change name of exe
                fs.copyFile(gameExe, "../games/" + nGames+1+".exe", (err) => {
                    if (err) throw err;
                    console.log('file was copied to games');
                });
                db.insert(gameName, gameAbout, gameExe);
            }
        })
    }
}