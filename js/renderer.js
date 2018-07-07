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
            var list = document.getElementsByClassName("li")
            //appending to gamelist display
            var table = document.getElementById('list');
            console.log("list" + list);
            var ArrGames = [];
            console.log(table)
			for (var i = 0; i < ArrNames.length-1; i++) {
                var li = document.createElement("li");
                var div = document.createElement("div");
                var a = document.createElement("a");
                var span1 = document.createElement("span");
                var span2 = document.createElement("span");
                span1.appendChild(document.createTextNode(ArrNames[i]));
                span1.className = "label";
                span2.className = "aboutgame";
                a.href = "javascript: void(0)";
                div.id = i
                div.onclick = () => { runGame("dss" + i)};
                span2.appendChild(document.createTextNode(ArrAbout[i]));
                li.appendChild(span1);
                li.appendChild(span2);
                li.className = "entries";
                a.appendChild(li);
                div.appendChild(a);

                table.appendChild(div);
			}
        }
    }); 
}

dbData_callback();
