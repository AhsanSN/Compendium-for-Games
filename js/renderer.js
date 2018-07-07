const db = require('../database.js')
const { ipcRenderer } = require('electron');

function runGame(gameIndex) {
    var gameName = "../games/game" + gameIndex + ".exe";
    console.log(gameName)
    ipcRenderer.send('runGame', "asd");
    //db.runExe(gameName)
}

function dbData_callback(){
    //get data from db
    var imgArray = db.getRows(function (err, data) {
        if (err) {
            console.log("ERROR : ", err);
        } else {
            var ArrNames = db.getArrayGName(data)
            var ArrAbout = db.getArrayGAbout(data)
            var ArrExe = db.getArrayGExe(data)

            console.log(itemLists)
            //appending to gamelist display
            var table = document.getElementById('list');
            var ArrGames = [];
            console.log(table)
			for (var i = 0; i < ArrNames.length-1; i++) {
                var li = document.createElement("li");
                var span1 = document.createElement("span");
                var span2 = document.createElement("span");
                span1.appendChild(document.createTextNode(ArrNames[i]));
                span1.className = "label";
                span2.className = "aboutgame";
                span2.appendChild(document.createTextNode(ArrAbout[i]));
                li.appendChild(span1);
                li.appendChild(span2);
                li.className = "entries";
                table.appendChild(li);

                //testing
            }
            var div = document.getElementById("list");
            var itemLists = div.getElementsByTagName("li")
            console.log("lis" +itemLists)

            for (var i = 0; i < ArrNames.length - 1; i++) {
                itemLists[i].i = i;
                itemLists[i].onclick = (function () {
                    var gameNumber = this.i;
                    runGame(gameNumber);
                    console.log("no "+this.i)
                });
            }

        }
    }); 
}

//dbData_callback();
window.onload = function () {
    dbData_callback();
 }
