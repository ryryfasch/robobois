const express = require("express");

const app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.set('view engine', 'ejs')
app.use(express.static('public'));

app.get('/', function(req, res){
  // res.render('index', {title: 'Search for whatever you want'});
})

app.post('/', function (req, res) {
  
  // res.render('index0');
})

app.listen((process.env.PORT || 3000), function () {
  console.log('Example app listening on port 3000!')
})
