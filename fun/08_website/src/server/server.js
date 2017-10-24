"use strict";

// Dependency
let fs = require('fs');
let https = require('https');
//MDTMP let WebSocketServer = require('ws').Server;

// Https server
let HTTPS_PORT = 8888;
let serverConfig = {
key: fs.readFileSync('ssl_keys/key.pem'),
     cert: fs.readFileSync('ssl_keys/cert.pem'),
};
let serverRequestHandle = function(request, response) {
    let filepath = 'public'.concat(request.url);
    if(filepath == 'public/') {
        filepath = 'public/index.html';
    }
    fs.access(filepath, (err) => {
        if (err) {
            if (err.code === 'ENOENT') {
                response.writeHead(404, { 'Content-Type': 'text/plain' });
                response.end('404 not found\n');
                return;
            }
            throw err;
        }

        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(fs.readFileSync(filepath));
    });
};

let httpsServer = https.createServer(serverConfig, serverRequestHandle);
httpsServer.listen(HTTPS_PORT, '0.0.0.0');

//MDTMP
// WebSocket server
/*
   let wss = new WebSocketServer({server: httpsServer});
   wss.on('connection', function(ws) {
   ws.on('message', function(message) {
   wss.broadcast(message);
   });
   });
   wss.broadcast = function(data) {
   for(let i in this.clients) {
   this.clients[i].send(data);
   }
   };
 */
