const electron = require('electron')
const url = require('url')
const path = require('path')
const fs = require('fs');
const express = require('express');
const db = require('./database.js')

const { app, BrowserWindow } = electron;
let mainWindow;

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

function dbData_callback(){
    //get data from db
    returnArray = [];
    var imgArray = db.getRows(function (err, data) {
        if (err) {
            console.log("ERROR : ", err);
        } else {
            var ArrNames = db.getArrayGName(data)
            var ArrAbout = db.getArrayGAbout(data)
            var ArrExe = db.getArrayGExe(data)
            returnArray.push(ArrNames);
            returnArray.push(ArrAbout);
            returnArray.push(ArrExe);
            console.log(returnArray)
        }
    }); 
}

app.on('ready', function () {
    showWindow();
    db.insert("Game1", "one of the best game", "gameexe.exe");
    //db.getRows()
    dbData_callback();
    
});

