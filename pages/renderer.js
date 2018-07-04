var ipc = require('electron').ipcRenderer;
var table = document.getElementById('todolist');
var li = document.createElement("li");
li.appendChild(document.createTextNode("AKHTUNBINSK"));
table.appendChild(li);

table.addEventListener('click', function(){
    ipc.on('actionReply', function(event, response){
        console.log("HTMLWala");
        console.log(response);
    })
    ipc.send('invokeAction', 'someData');
});