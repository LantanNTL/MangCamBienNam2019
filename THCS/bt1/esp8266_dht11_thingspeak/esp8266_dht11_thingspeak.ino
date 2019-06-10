#include <DHT.h>
#include <ESP8266WiFi.h>
#define DHTPIN D7
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "bamlanat"; 
const char* password = "chigooglecungbotay@123!!!"; 
WiFiClient client;

const int channelID = 709610; //
String writeAPIKey = "OYWO9E69Y8VXRXMO"; 
const char* server = "api.thingspeak.com";

void setup() {
        Serial.begin(9600);
        dht.begin();
        Serial.print("Connecting");
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
                Serial.print(".");
                delay(100);
        }
        Serial.println("\r\nWiFi connected");
}
void loop() {
        delay(2000);
        float temp = dht.readTemperature();
        float humi = dht.readHumidity();
        if (isnan(temp) || isnan(humi)) {
                Serial.println("Failed to read from DHT sensor!");
                return;
        }
        if (client.connect(server, 80)) {
                String body = "field1=" + String(temp, 1) + "&field2=" + String(humi, 1);
                client.print("POST /update HTTP/1.1\n");
                client.print("Host: api.thingspeak.com\n");
                client.print("Connection: close\n");
                client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
                client.print("Content-Type: application/x-www-form-urlencoded\n");
                client.print("Content-Length: ");
                client.print(body.length());
                client.print("\n\n");
                client.print(body);
                client.print("\n\n");
                Serial.printf("Nhiet do %s - Do am %s\r\n", String(temp, 2).c_str(), String(humi, 3).c_str());
        }
        client.stop();
}
