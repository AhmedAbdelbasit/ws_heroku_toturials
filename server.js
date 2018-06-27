'use strict';

const express = require('express');
const SocketServer = require('ws').Server;
const path = require('path');

const PORT = process.env.PORT || 3000;
const INDEX = path.join(__dirname, '/pages/index.html');

const server = express()
  .use((req, res) => res.sendFile(INDEX) )
  .listen(PORT, () => console.log(`Listening on ${ PORT }`));

const wss = new SocketServer({ server });

wss.on('connection', (ws) => {
	wss.on('message', function(msg) {
		message = JSON.parse(msg);
		if(message.cmd == "light"){
			if(message.val == "on"){
				var xmlHttp = new XMLHttpRequest();
				xmlHttp.open( "GET", "https://dweet.io/dweet/for/home?light=on", false ); // false for synchronous request
				xmlHttp.send( null );
			}else{
				var xmlHttp = new XMLHttpRequest();
				xmlHttp.open( "GET", "https://dweet.io/dweet/for/home?light=off", false ); // false for synchronous request
				xmlHttp.send( null );
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