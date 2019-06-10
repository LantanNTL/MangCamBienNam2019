/*---------------------------------------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
/*---------------------------------------------------------------------------------------------------------------*/
const char *ssid = "bamlanat";      
const char *password = "chigooglecungbotay@123!!!";   
//const char *ssid = "huongnguyen";      
//const char *password = "123456789";    
//const char* ssid     = "iPhone";
//const char* password = "quocanh12";       
ESP8266WebServer server(80);           
int led1 = D1;
int led2 = D2;
/*---------------------------------------------------------------------------------------------------------------*/
void handleRoot() {                    
    response();
} 
void handleLedOn1() {
  digitalWrite(led1, HIGH);       
  response();                          
}
void handleLedOff1() {
  digitalWrite(led1, LOW);
  response();
}
void handleLedOn2() {
  digitalWrite(led2, HIGH);       
  response();                          
}
void handleLedOff2() {
  digitalWrite(led2, LOW);
  response();
}
/*---------------------------------------------------------------------------------------------------------------*/
void response(){                        
  String s;
  s = "<!DOCTYPE html>"
  "<html>"
    "<title>Button</title>"
  "<head>"
  "<style>"
    "a {text-decoration:none;}"
    ".css_on {width:150px;height:50px;color:white;font-size:14px;background-color:#195B6A}"
    ".css_off{width:150px;height:50px;font-size:14px;background-color:#77878A}"
  "</style><head>"
  "<body style='background-color:#c3eef4'>"
    "<center>"
      "<h1 style='color:#ff0000'>ESP8266 Web Server </h1>"
      "<a href='LEDon1'>"
        "<h2 style='color:green'> Button 1 </h2>"
        "<button type='button' class='css_on'>ON1</button>"
      "</a>"
      "<a href='LEDoff1'>"
        "<button type='button' class='css_off'>OFF1</button>"
      "</a>"
      "<a href='LEDon2'>"
        "<h2 style='color:#047559'> Button 2 </h2>"
        "<button type='button' class='css_on'>ON2</button>"
      "</a>"
      "<a href='LEDoff2'>"
        "<button type='button' class='css_off'>OFF1</button>"
      "</a>"
      "<img src='http://360.thuvienvatly.com/images/2014/02/light-bulb-02.jpg' style='width:300px;height:300px;padding:20px;display:block;'>"
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
    server.on("/LEDon1", handleLedOn1);         
    server.on("/LEDoff1", handleLedOff1);
    server.on("/", handleRoot); 
    server.on("/LEDon2", handleLedOn2);         
    server.on("/LEDoff2", handleLedOff2);
    server.begin();                         
    Serial.println("HTTP server beginned");
    pinMode(led1, OUTPUT);            
    digitalWrite(led1, LOW); 
    pinMode(led2, OUTPUT);            
    digitalWrite(led2, LOW);          
}
 
void loop() {
    server.handleClient();             
}
