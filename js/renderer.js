const db = require('../database.js')

function runGame(gameIndex) {
    console.log(gameIndex)
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
                        console.log("no "+this.i)
                        // TODO ---
                        // Your handler code here
                });
            }

        }
    }); 
}

//dbData_callback();
window.onload = function () {
    dbData_callback();
 }
