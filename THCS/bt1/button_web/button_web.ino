/*---------------------------------------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
/*---------------------------------------------------------------------------------------------------------------*/
//const char *ssid = "bamlanat";      
//const char *password = "chigooglecungbotay@123!!!"; 
const char *ssid = "Redmi";      
const char *password = "999999999";
            
ESP8266WebServer server(80);           
int led = D1;
/*---------------------------------------------------------------------------------------------------------------*/
void handleRoot() {                    
    response();
} 
void handleLedOn() {
  digitalWrite(led, HIGH);       
  response();                          
}
void handleLedOff() {
  digitalWrite(led, LOW);
  response();
}
/*---------------------------------------------------------------------------------------------------------------*/
void response(){                        
  String s;
  s = "<!DOCTYPE html>"
  "<html>"
    "<title>Control Led </title>"
  "<head>"
  "<style>"
    "a {text-decoration:none;}"
    ".css {display:block;width:150px;height:50px;font-size:14px;border-radius:8px}"
    ".on {color:white;background-color:#195B6A}"
    ".off {background-color:#77878A}"
  "</style><head>"
  "<body>"
    "<center>"
      "<a href='LEDOn'>"
        "<h1> Button</h1>"
        "<button type='button' class='css on'>ON</button>"
      "</a>"
      "<a href='LEDOff'>"
        "<button type='button' class='css off'>OFF</button>"
      "</a>"
    "</center>"
  "</body>"
  "</html>";
 
  server.send(200, "text/html", s);
}
/*---------------------------------------------------------------------------------------------------------------*/
void setup() {
    delay(1000);
    Serial.begin(115200);
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
    Serial.println("WiFi connected!");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    
    server.on("/", handleRoot);              
    server.on("/LEDOn", handleLedOn);         
    server.on("/LEDOff", handleLedOff);
    server.begin();                         
    Serial.println("HTTP server beginned");
    pinMode(led, OUTPUT);            
    digitalWrite(led, LOW);           
}
 
void loop() {
    server.handleClient();             
}
