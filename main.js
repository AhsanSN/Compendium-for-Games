const electron = require('electron')
const url = require('url')
const path = require('path')
const express = require('express');

const { app, BrowserWindow } = electron;
let mainWindow;

function showWindow() {

    mainWindow = new BrowserWindow({})
    mainWindow.setMenu(null);
    mainWindow.setTitle("HU - Compendium for games");
    mainWindow.setSize(800, 600, 1);
    mainWindow.setResizable(true)
    mainWindow.toggleDevTools();

    mainWindow.loadURL(url.format({
        pathname: path.join(__dirname, '/pages/home.html'),
        protocol: 'file:',
        slashes: true
    }));
}

function openDialog() {
    const dialog = require('electron').dialog;
    console.log(dialog.showOpenDialog({
        title: 'Select Game Exe (.exe)', filters: [
            { name: 'Executable (.exe)', extensions: ['exe'] },
        ], properties: ['openFile']
    }));
}

app.on('ready', function () {
    showWindow();
});



