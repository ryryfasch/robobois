const express = require("express");
var SerialPort = require('serialport');

const app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.set('view engine', 'ejs')
app.use(express.static('public'));

var serialPort = new SerialPort("COM11", {
   baudRate: 9600
});

var serialPortCallback = function(err) {
   if(err) {
       console.log("Error on write: ", err.message);
   }
};

app.get('/', function(req, res){
  // res.render('index', {title: 'Search for whatever you want'});
})

app.post('/', function (req, res) {
  serialPort.on('open', function() {
     console.log("Connected\n");
     serialPort.write(req.body.command, serialPortCallback);
  });
  // res.render('index0');
})

app.listen((process.env.PORT || 3000), function () {
  console.log('Example app listening on port 3000!')
})
