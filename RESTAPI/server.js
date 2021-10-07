
var express = require('express');
var config = require('./config.js');
var fileSystem = require('fs');

var app = express();

app.use(express.json());

app.get('/config', function (request, response) {
  console.log('config get');
  
  const filename = './Responses/basic.xml'; 
  fileSystem.exists(filename,  function(exists) {
    if(exists) {
      const fileContent = fileSystem.readFileSync(filename, 'utf8');
      response.set('Content-Type', 'text/xml');
      response.send(fileContent);
    }
  });
});

app.put('/config', (req, res) => {
  console.log('config put');

});



//app.listen(8000, function(){
app.listen(config.basePort, function(){
  console.log("Listening port " + config.basePort);
})
