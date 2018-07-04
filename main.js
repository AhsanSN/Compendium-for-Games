const electron = require('electron')
const url = require('url')
const path = require('path')
const fs = require('fs');
const express = require('express');
const db = require('./database.js')

const { app, BrowserWindow } = electron;
let mainWindow;

var ipc = require('electron').ipcMain;

ipc.on('invokeAction', function(event, data){
    
    console.log(data);
    event.sender.send('actionReply', "Lmao");
    console.log("ADWA");
});

function readFile()
{

    var games;
    fs.readFile('gameList.txt', function (error, data) {
        if (!error)
        {
            games = data.toString().split("\n");
            noOfGames = games.length;
            ipc.on('gamelistSent',function(event,arg)
            {
                event.sender.send(games);
            });
        }
    });

}

function showWindow() {

    mainWindow = new BrowserWindow({})
    mainWindow.setMenu(null);
    mainWindow.setTitle("HU - Compendium for games");
    mainWindow.setSize(800, 600, 1);
    mainWindow.setResizable(true)

    mainWindow.loadURL(url.format({
        pathname: path.join(__dirname, '/pages/home.html'),
        protocol: 'file:',
        slashes: true
    }));
}

app.on('ready', function () {
    showWindow();
    db.createTable();
    db.insert();
    readFile();
});

