var express = require('express');
var config = require('./config.js');
var fileSystem = require('fs');

var app = express();

app.use(express.json());

app.get('/configuration', function (request, response) {
  console.log('configuration get');
  
  const filename = './Responses/basic.xml'; 
  fileSystem.exists(filename,  function(exists) {
    if(exists) {
      const fileContent = fileSystem.readFileSync(filename, 'utf8');
      response.set('Content-Type', 'text/xml');
      response.send(fileContent);
    }
  });
});

app.put('/configuration', (request, response) => {
  console.log('configuration put');

  const filename = './Responses/basicReq.xml';
  const data = request.query['xmlFileContent']; 
  fileSystem.writeFileSync(filename, data);
  response.status(200).send('ok');
});

app.get('/image', function (request, response) {
  console.log('image get');
  
  const filename = './Responses/Image.jpg'; 
  fileSystem.exists(filename,  function(exists) {
    if(exists) {
      const imageContent = fileSystem.readFileSync(filename);
      console.log('image found');
      response.writeHead(200, {'Content-Type': 'image/jpeg'});
      response.end(imageContent); 
    }
  });
});

app.listen(config.basePort, function(){
  console.log("Listening port " + config.basePort);
})
