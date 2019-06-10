var express = require('express');
var app = express();

app.use(express.static("public"));
app.set("view engine", "ejs");
app.set("views", "./views");


var server = require('http').Server(app);
var io = require('socket.io')(server);

var mysql= require('mysql');
var connection = mysql.createConnection({
  host: 'localhost',
  user: 'wsn',
  password: '1',
  database: 'wsn'
});
connection.connect((err) => {
  if (err) throw err;
  console.log('Connected!');
});

app.get('/', function(req, res) {

    connection.query("SELECT * FROM sensors ORDER BY id DESC limit 7",(err, result) => {
        if(err) {
            console.log(err); 
        }
        else { 
            var temp =[];
            var hum = [];
            var time = [];
            var result = JSON.stringify(result);
            result = JSON.parse(result);
            for(var i=0;i<result.length;i++)
            {
                temp[i] = result[i].Temperature;
                hum[i]  = result[i].Humidity;
                time[i] = result[i].Date_and_Time;
            }
            res.render('pages/index',{
                temp: temp,
                hum: hum,
                time :time 
            });
        }
    });
});

var status="";
var value = 0;    
io.on('connection', function(socket) {
  console.log('ID' + socket.id + '--connected');
  socket.emit('welcome', socket.id);
   //Whenever someone disconnects this piece of code executed
  socket.on('disconnect', function () {
      console.log('ID' + socket.id +'--disconnected');
  });
  socket.on('ledStatus', function(message) {
      message = JSON.parse(message);
      status = message.status;
      io.sockets.emit('ledStatus',message.status);
      console.log(status);
  });
  socket.on('brightness', function(message) {
      io.sockets.emit('brightness', message);
      value = message;
      console.log(message);
  });
});
server.listen(3000, function() {
   console.log('listening on *:3000');
});