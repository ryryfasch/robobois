const express = require("express");
const bodyParser = require('body-parser');
var SerialPort = require('serialport');
const util = require('util');

const app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.set('views', __dirname + '/views');
app.set('view engine', 'html');
app.use(express.static(__dirname + '/views'));
// app.use(express.static('public'));

// SerialPort.list(function (err, ports) {
//   ports.forEach(function(port) {
//     console.log(port);
//   });
// });

var command = "";
var serialPort = new SerialPort("COM11", {
   baudRate: 9600
});

var serialPortCallback = function(err) {
   if(err) {
       console.log("Error on write: ", err.message);
   }
};



app.get('/', function(req, res){
  res.sendFile(__dirname + '/views/index.html');
  // res.render('index', {title: 'Search for whatever you want'});
  serialPort.on('open', function() {
    console.log("Connected1\n");
    // serialPort.write('f', serialPortCallback);
 });
})

app.post('/', function (req, res) {
    console.log("request " + req.body.command);
    // console.log(util.inspect(req.body.command, {showHidden: false, depth: null}))

    if(req.body.command == "forward"){
      command = "forward";
      serialPort.on('open', function() {
         console.log("Connected2\n");
         serialPort.write(command, serialPortCallback);
      });
    }
    if(req.body.command == "backward"){
      command = "backward";
      serialPort.on('open', function() {
         console.log("Connected2\n");
         serialPort.write(command, serialPortCallback);
      });
    }
    if(req.body.command == "turn left"){
      command = "left"; // 90 degree turn
      serialPort.on('open', function() {
         console.log("Connected2\n");
         serialPort.write(command, serialPortCallback);
      });
    }
    if(req.body.command == "turn right"){
      command = "right"; // 90 degree turn
      serialPort.on('open', function() {
         console.log("Connected2\n");
         serialPort.write(command, serialPortCallback);
      });
    }
    if(req.body.command == "stop"){
      command == "stop";
      serialPort.on('open', function() {
         console.log("Connected2\n");
         serialPort.write(command, serialPortCallback);
      });
    }
  // res.render('index0');
})

app.listen((process.env.PORT || 3000), function () {
  console.log('Example app listening on port 3000!')
})
