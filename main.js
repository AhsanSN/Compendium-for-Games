const electron = require('electron')
const url = require('url')
const path = require('path')
const express = require('express');
const fs = require('fs');

const { app, BrowserWindow } = electron;
let mainWindow;

function showWindow() {

    mainWindow = new BrowserWindow({})
    mainWindow.setMenu(null);
    mainWindow.setTitle("HU - Compendium for games");
    mainWindow.setSize(800, 600, 1);
    mainWindow.setResizable(true)
    //mainWindow.toggleDevTools();

    mainWindow.loadURL(url.format({
        pathname: path.join(__dirname, '/pages/home.html'),
        protocol: 'file:',
        slashes: true
    }));
}

function sigOpenWindow() {
    const { ipcMain } = require('electron')
    ipcMain.on('asynchronous-message', (event, arg) => {
        var exeFile = openDialog();
        console.log("requesting fileupload window")
        event.sender.send('asynchronous-reply', exeFile[0])
        event.returnValue = 'pong'
    })
    ipcMain.on('runGame', (event, arg) => {
        console.log("received game signal")
    })
}
    

function openDialog() {
    var exeFile;
    const dialog = require('electron').dialog;
    exeFile = (dialog.showOpenDialog({
        title: 'Select Game Folder (Images, exes, etc)', filters: [
            { name: 'Game Executable (.exe)'},
        ], properties: ['openDirectory']
    }));
    console.log("asdasdasd" + exeFile)
    getFilesFromDir("C:\Users\Ahsan Ahmed\Documents\GitHub\Compendium-for-Games");
    return exeFile;
}

app.on('ready', function () {
    showWindow();
    sigOpenWindow();
});

function getFilesFromDir(dir) {
    fs.readdir(dir, function (dir) {
        for (var i = 0, l = dir.length; i < l; i++) {
            var filePath = dir[i];
            console.log(filePath)
        }
    });
}


