<<<<<<< HEAD
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
				li.appendChild(document.createTextNode(ArrNames[i]));
				//make this small
				li.appendChild(document.createTextNode(ArrAbout[i]));
				table.appendChild(li);
			}
        }
    }); 
}

dbData_callback();
