// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include "DHT.h"

#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
// Replace with your network credentials
const char* ssid     = "bamlanat";
const char* password = "chigooglecungbotay@123!!!";

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
            if(isnan(h) || isnan(t)){
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
                    if (header.indexOf("GET /5/on") >= 0) {
                        Serial.println("GPIO 5 on");
                        output5State = "on";
                        digitalWrite(output5, HIGH);
                    } 
                    else if(header.indexOf("GET /5/off") >= 0){
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
                    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                    client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
                    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                    client.println(".image{width: 250px; height: 250px; padding-top : 10px; padding-left:250px;float: left; }");
                    client.println(".button2 {background-color: #77878A;}</style></head>");
            
                    // Web Page Heading
                    client.println("<body style='background-color:#c3eef4'><h1>ESP8266 Web Server</h1>");
                    client.println("<img class='image' alt='Ngo Thi La' aria-busy='false' src='https://scontent.fhan2-4.fna.fbcdn.net/v/t1.0-9/51791377_629818860812395_8873567927215849472_n.jpg?_nc_cat=104&amp;_nc_oc=AQlK2YTDNelNsdm-c6SCG-5eYtskpZAcGhN7x_CUAH4qy-J0hOlwGwg0cfDlzIn01uMmb-G1e2ovpgFsnI6WSHjQ&amp;_nc_ht=scontent.fhan2-4.fna&amp;oh=2cbe383efa236da5af04e9e94ee56673&amp;oe=5D4D6F76' >");
                    client.println("<h3>Temperature : ");
                    client.println(t);
                    client.println("*C</h3><h3>Humidity :");
                    client.println(h);
                    client.println("%</h3><h3>");
                    // Display current state, and ON/OFF buttons for GPIO 5  
                    client.println("<p>GPIO 5 - State " + output5State + "</p>");
                    // If the output5State is off, it displays the ON button       
                    if (output5State=="off") {
                        client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
                        client.println("<img style='-webkit-user-select: none;' src='http://i.imgur.com/T5H4MHE.png'%20class='card-img-top' width='100' height='100'>");
                    } 
                    else{
                        client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
                        client.println("<img style='-webkit-user-select: none;cursor: zoom-out;' src='https://proxy.spigotmc.org/c5438d3cd4f3b3aee4526158689bacfc35a9c218?url=http%3A%2F%2Fblogs.psychcentral.com%2Ftherapy-soup%2Ffiles%2F2013%2F11%2F190593_4590.jpg' width='100' height='100'>");
                    } 
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
