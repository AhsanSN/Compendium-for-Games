const db = require('../database.js')

function dbData_callback(){
    //get data from db
    var imgArray = db.getRows(function (err, data) {
        if (err) {
            console.log("ERROR : ", err);
        } else {
            var ArrNames = db.getArrayGName(data)
            var ArrAbout = db.getArrayGAbout(data)
            var ArrExe = db.getArrayGExe(data)

            //appending to gamelist display
            var table = document.getElementById('todolist');

			for (var i = 0; i < ArrNames.length; i++) {
                var li = document.createElement("li");
                var a = document.createElement("a");
                var span1 = document.createElement("span");
                var span2 = document.createElement("span");
                span1.appendChild(document.createTextNode(ArrNames[i]));
                span1.className = "label";
                span2.className = "aboutgame";
                li.onclick = ()=>{lma();};
                span2.appendChild(document.createTextNode(ArrAbout[i]));
                li.appendChild(span1);
                li.appendChild(span2);
                a.appendChild(li);
				table.appendChild(a);
			}
        }
    }); 
}

function lma()
{
    console.log("Click");
}

dbData_callback();
