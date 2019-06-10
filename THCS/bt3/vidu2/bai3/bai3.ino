#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const char *ssid = "huongnguyen";      
const char *password = "123456789";
const char* mqttServer = "192.168.43.160";
const char* mqttUser = "";
const char* mqttPassword = "";
const int mqttPort = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMeasure = 0;
long now = millis();
//buff_msg[32]; // mqtt message
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to WiFi..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //thiet lap dia chi va cong may chu MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  //ket noi den may chu MQTT
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client",mqttUser,mqttPassword)) {
      Serial.println("connected");
    } 
    else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
        }
    client.publish("home/sensors", "Hello ESP world");
    }
}
void reconnect() {
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("ESP8266Client",mqttUser,mqttPassword)) {
      Serial.println("connected");
      // Khi kết nối sẽ publish thông báo
      client.publish("home/sensors", "ESP_reconnected");
      // ... và nhận lại thông tin này
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

   
    // Publishes new temperature and humidity
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("\nFailed to read from DHT sensor!");
      return;
    }
    data["Temperature"] = int(t) ;
    data["Humidity"] = int(h);
    char payload[];
    data.printTo(payload, sizeof(payload));
    String strPayload = String(payload);
    Serial.print("Format data: ");
    Serial.println(strPayload);
    client.publish("test", strPayload.c_str());
    
    Serial.print("\nHumidity: ");
    Serial.print(h);
    Serial.print(" %\t Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("\n ");
  }    
}
