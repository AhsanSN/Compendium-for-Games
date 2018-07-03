const electron = require('electron')
const url = require('url')
const path = require('path')
const fs = require('fs');
const express = require('express');
// const request = require('request');
var stream = fs.createWriteStream("imagesFile.txt", { flags: 'a' });

const { app, BrowserWindow } = electron;
let mainWindow;


function showWindow() {

    mainWindow = new BrowserWindow({})
    mainWindow.setMenu(null);
    mainWindow.setTitle("HU - Compendium for games");
    mainWindow.setSize(800, 600, 1);
    mainWindow.setResizable(false)

    mainWindow.loadURL(url.format({
        pathname: path.join(__dirname, '/pages/home.html'),
        protocol: 'file:',
        slashes: true
    }));
}

app.on('ready', function () {
    showWindow();
});

