// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include "DHT.h"

#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
// Replace with your network credentials
const char* ssid     = "huongnguyen";
const char* password = "123456789";
//const char* ssid     = "cobanben";
//const char* password = "mylinh123";
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {                             // If a new client connects,
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            float h = dht.readHumidity();
            float t = dht.readTemperature();
            if(isnan(h) || isnan(t) ){
                Serial.println("Failed to read from DHT11");  
            }
            else{
                Serial.print("Humidity: ");
                Serial.print(h);
                Serial.print(" %\t Temperature: ");
                Serial.print(t);
                Serial.println(" *C "); 
            }
            
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                header += c;
                if (c == '\n') {                    // if the byte is a newline character
                // if the current line is blank, you got two newline characters in a row.
                // that's the end of the client HTTP request, so send a response:
                if (currentLine.length() == 0) {
                // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                // and a content-type so the client knows what's coming, then a blank line:
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();
            
                    // turns the GPIOs on and off
                    if (header.indexOf("GET /on") >= 0) {
                        Serial.println("GPIO 5 on");
                        output5State = "on";
                        digitalWrite(output5, HIGH);
                    } 
                    else if(header.indexOf("GET /off") >= 0){
                        Serial.println("GPIO 5 off");
                        output5State = "off";
                        digitalWrite(output5, LOW);
                    } 
            
                    // Display the HTML web page
                    client.println("<!DOCTYPE html><html>");
                    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                    client.println("<link rel=\"icon\" href=\"data:,\">");
                    // CSS to style the on/off buttons 
                    // Feel free to change the background-color and font-size attributes to fit your preferences
                    client.println("<style>");
                    client.println("body {background-image: url('https://png.pngtree.com/thumb_back/fw800/back_pic/05/06/42/22596e019341802.jpg');background-size: 100% 100%;}");
                    client.println(".web-text{text-align: center;color: red;top: 20%;left: 50%;position: absolute;transform: translate(-50%, -50%);font-size: 30px;}");
                    client.println(".sensor{height: 800px;background-position: center;background-size: cover;}");
                    client.println(".card .card-img-top{margin-top:250px;width: 200px;height: 200px;}");
                    client.println(".car .card-body{font-size: 25px;text-align: center;}");
                    client.println(".temp{float: left;margin-left:230px; margin-top:50px;}");
                    client.println(".css_on {width:200px;height:50px;color:white;font-size:14px;background-color:#195B6A}");
                    client.println(".css_off {width:200px;height:50px;font-size:14px;ackground-color:#77878A}");
                    client.println("</style></head>");
                    // Web Page Heading
                    client.println("<body><div class='bodyweb'><div class='sensor'>");
                    client.println("<div class ='web-text'><h1>ESP8266 Web Server</h1></div>");
                    client.println("<div class='temp'><div class='card'>");
                    client.println("<img src='http://haircompanion.co.uk/wp-content/uploads/2016/02/temperature-controlled.jpg' class='card-img-top' alt='...'>");
                    client.println("<div class='card-body'><h3>Temperature: ");
                    client.println(t);
                    client.println(" °C</h3></div></div></div>");
                    client.println("<div class='temp'><div class='card'>");
                    client.println("<img src='https://media.istockphoto.com/vectors/humidity-icon-isolated-with-long-shadow-weather-and-meteorology-vector-id939156212?k=6&m=939156212&s=612x612&w=0&h=42VaKPTYEEIgsBWko3HpofR_I5EheqlknVjtsVAoHlY=' class='card-img-top' alt='...'>");
                    client.println("<div class='hum'><h3 style='text-align: center'>Humidity: ");
                    client.println(h);
                    client.println(" %</h3></div></div></div>");
                    if (output5State=="off") {
                        client.println("<div class='temp'><div class='card'>");
                        client.println("<img src='http://genknews.genkcdn.vn/N0WoyYblO3QdmZFKPMtKnadHAHTevz/Image/2012/03/8_ebc8e.jpg' class='card-img-top'>");
                        client.println("<h3 style='text-align: center'>Light - Status : " + output5State + "</h3>");
                        client.println("<p><a href=\"/on\"><button class='css_on'>ON</button></a></p>");
                        client.println("</div></div>");
                    } 
                    else{
                        client.println("<div class='temp'><div class='card'>");
                        client.println("<img src='http://www.livescience.com/images/i/000/002/759/original/081209-light-bulb-02.jpg?interpolation\x3dlanczos-none\x26downsize\x3d*:1000' class='card-img-top'>");
                        client.println("<h3 style='text-align: center'>Light - Status : " + output5State + "</h3>");
                        client.println("<p><a href=\"/off\"><button class='css_off'>OFF</button></a></p>");
                        client.println("</div></div>");
                    }
                    client.println("</div></div>");
                    client.println("</body></html>");
            
                    // The HTTP response ends with another blank line
                    client.println();
                    // Break out of the while loop
                    break;
                }
                else { // if you got a newline, then clear currentLine
                    currentLine = "";
                }
            } 
            else if (c != '\r') {  // if you got anything else but a carriage return character,
                currentLine += c;      // add it to the end of the currentLine
            }
        }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    }
}
