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

app.listen(config.basePort, function(){
  console.log("Listening port " + config.basePort);
})
