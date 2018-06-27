'use strict';

const express = require('express');
const SocketServer = require('ws').Server;
const path = require('path');
const https = require('https');

const PORT = process.env.PORT || 3000;
const INDEX = path.join(__dirname, '/pages/index.html');

const server = express()
  .use((req, res) => res.sendFile(INDEX) )
  .listen(PORT, () => console.log(`Listening on ${ PORT }`));

const wss = new SocketServer({ server });

wss.on('connection', (ws) => {
	ws.on('message', function(msg) {
		var message = JSON.parse(msg);
		console.log(message.cmd);
		if(message.cmd == "light"){
			console.log(message.val);
			if(message.val == "on"){
				https.get('https://dweet.io/dweet/for/home?light=on', (resp) => {
					
				}).on("error", (err) => {
					console.log("Error: " + err.message);
				});
			}else{
				https.get('https://dweet.io/dweet/for/home?light=off', (resp) => {
					
				}).on("error", (err) => {
					console.log("Error: " + err.message);
				});
			}
		}else{
			
		}			
		
	});
	
	console.log('Client connected');
	ws.on('close', () => console.log('Client disconnected'));
});



setInterval(() => {
  wss.clients.forEach((client) => {
    client.send(new Date().toTimeString());
  });
}, 1000);


//var HOST = "ws://localhost:3000";



/*
//var xmlHttp = new XMLHttpRequest();
				//xmlHttp.open( "GET", "https://dweet.io/dweet/for/home?light=off", false ); // false for synchronous request
				//xmlHttp.send( null );				
				
				//document.getElementById("lightState").style.fill = 'red';
*/

/*
			
			ws.onopen = function(){
				if(AccountName != ""){
					UserName = AccountName;
					friendname = prompt('what is your friend username ?');
					sock.send(JSON.stringify({
						type: "open_chat",
						fromname: AccountName.trim(),
						toname: friendname
					}));
				}else{
					window.location.replace("../home/login.php");
				}
			}
			
			sock.onmessage = function(event){
				console.log(event);
				var json = JSON.parse(event.data);
				if(json.name=="You"){
					log.innerHTML += ("<div style=\"display: inline; word-wrap: break-word; width: 180px; overflow-y: auto; border-radius: 15px; float: right; background: white; padding: 7px; border: solid 1px black;\"> <span style=\"color: red;\">"+ json.name +": "+ "<span style=\"color: blue;\"> "+json.data + "</span></div><br/><br/>");
				}else{
					log.innerHTML += ("<div style=\"display: inline; word-wrap: break-word; width: 180px; overflow-y: auto; border-radius: 15px; float: left;  background: yellow; padding: 7px; border: solid 1px black;\"> <span style=\"color: red;\">"+ json.name +": "+ "<span style=\"color: blue;\"> "+json.data + "</span></div><br/><br/>");
				}
				//word-break: break-all; word-wrap: break-word;
				//log.innerHTML += '<div style="float: right;"> <span style="color: red;">'+ json.name +": "+ '<span style="color: blue;"> '+json.data + '</span></div>'+'<br/>';
				$('#log').animate({scrollTop: $('#log').prop("scrollHeight")}, 10);
				
			}
			
			*/
			
 
/*https.get('https://api.nasa.gov/planetary/apod?api_key=DEMO_KEY', (resp) => {
  let data = '';
 
  // A chunk of data has been recieved.
  resp.on('data', (chunk) => {
    data += chunk;
  });
 
  // The whole response has been received. Print out the result.
  resp.on('end', () => {
    console.log(JSON.parse(data).explanation);
  });
 
}).on("error", (err) => {
  console.log("Error: " + err.message);
});*/