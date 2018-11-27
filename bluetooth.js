var SerialPort = require('serialport');

var serialPort = new SerialPort("COM11", {
   baudRate: 9600
});

var serialPortCallback = function(err) {
   if(err) {
       console.log("Error on write: ", err.message);
   }
};

serialPort.on('open', function() {
   console.log("Connected\n");
   serialPort.write('a', serialPortCallback);
});

serialPort.on('error', function(err){
   console.log("Error: ", err.message);
});

serialPort.on('close', function() {
   console.log("Closed");
});
