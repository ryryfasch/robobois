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


var serialPort = new SerialPort("COM5", {
   baudRate: 9600
});

var serialPortCallback = function(err) {
   if(err) {
       console.log("Error on write: ", err.message);
   }
};

serialPort.on('open', function() {
  console.log("Connected1\n");
  // serialPort.write('f', serialPortCallback);
  app.get('/', function(req, res){
    res.sendFile(__dirname + '/views/index.html');

    // res.render('index', {title: 'Search for whatever you want'});
  })

  app.post('/', function (req, res) {
      // console.log("request " + req.body);
      // console.log(util.inspect(req.body, {showHidden: false, depth: null}))

      var command = '';
      // console.log(util.inspect(req.body, {showHidden: false, depth: null}))

      if(req.body.command.indexOf("forward") != -1){
        if(req.body.command.split(" ")[1]){
          command = 'f ' + req.body.command.split(" ")[1];
        } else{
          command = 'f';
        }
        console.log(command);
      }
      if(req.body.command.indexOf("left") != -1){
        if(req.body.command.split(" ")[1]){
          command = 'l ' +  req.body.command.split(" ")[1];
          console.log(command);
        } else {
          command = 'l';
        }
        console.log(command);
      }
      if(req.body.command.indexOf("right") != -1){
        if(req.body.command.split(" ")[1]){
          command = 'r ' + req.body.command.split(" ")[1];
          console.log(command);
        } else{
          command = 'r';
        }
        console.log(command);
      }
      if(req.body.command.indexOf("stop") != -1){
        if(req.body.command.split(" ")[1]){
          command = 's ' + req.body.command.split(" ")[1];
          console.log(command);
        } else{
          command = 's';
        }
      }
      if(req.body.command.indexOf("grab") != -1){
        if(req.body.command.split(" ")[1]){
          command = 'g ' + req.body.command.split(" ")[1];
          console.log(command);
        } else{
          command = 'g';
        }
      }
      if(req.body.command.indexOf("exit") != -1){
        if(req.body.command.split(" ")[1]){
          command = 'e ' + req.body.command.split(" ")[1];
          console.log(command);
        } else{
          command = 'e';
        }
      }
      if(req.body.command.indexOf("dance") != -1){
        if(req.body.command.split(" ")[1]){
          command = 'm ' + req.body.command.split(" ")[1];
          console.log(command);
        } else{
          command = 'm';
        }
      }
      serialPort.write(command, serialPortCallback);
    // serialPort.on('open', function() {
    //    console.log("Connected2\n");
    //    serialPort.write(req.body.command, serialPortCallback);
    // });
    // res.render('index0');
  })
});

app.listen((process.env.PORT || 3000), function () {
  console.log('Example app listening on port 3000!')
})
