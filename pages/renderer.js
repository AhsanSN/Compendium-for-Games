var ipc = require('electron').ipcRenderer;
var table = document.getElementById('todolist');
var li = document.createElement("li");
li.appendChild(document.createTextNode("AKHTUNBINSK"));
table.appendChild(li);

table.addEventListener('click', function(event){
    ipc.send('invokeAction', "event");
    console.log("WAD");
    ipc.on('actionReply', function(event, response){
        console.log("Chu");
    })
});



ipc.on('gamelistSent',function(event,arg)
{
    for (var i = 0; i<arg.length;i++)
    console.log(arg[i]);
})

console.log(ipc.sendSync('synchronous-message', 'ping')) // prints "pong"

ipc.on('asynchronous-reply', (event, arg) => {
  console.log(arg) // prints "pong"
})
ipc.send('asynchronous-message', 'ping')