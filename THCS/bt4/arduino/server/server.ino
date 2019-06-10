#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#define DHTTYPE DHT11   // DHT 11
#define ssid "huongnguyen"
#define password "123456789"
// Thông tin về MQTT Broker
#define mqtt_server "192.168.43.160" // Thay bằng địa chỉ IP 
//#define ssid "2 anh hang xom tot bung"
//#define password "30261997"
//// Thông tin về MQTT Broker
//#define mqtt_server "192.168.43.190" // Thay bằng địa chỉ IP 
#define mqtt_topic_pub "test"   //Giữ nguyên nếu bạn tạo topic tên là demo
#define mqtt_topic_sub "test"
#define mqtt_user ""    //Giữ nguyên nếu bạn tạo user là lophocvui và pass là 123456
#define mqtt_pass ""
 
const uint16_t mqtt_port = 1883; //Port của MQTT
 
WiFiClient espClient;
PubSubClient client(espClient);
 
const int DHTPin = D5;       //Đọc dữ liệu từ DHT11 ở chân D5 trên mạch esp8266
 
long lastMsg = 0;
char msg[50];
int value = 0;
// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Thiet Lap cam bien DHT.
DHT dht(DHTPin, DHTTYPE);
//GPIO 5 = D1
const int led = D1;
//GPIO 4 = D2
const int bright = D0;

const long utcOffsetInSeconds = 7*60*60;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);
String formattedDate;
String dayStamp;
String timeStamp;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  pinMode(led, OUTPUT);
  pinMode(bright, OUTPUT);
  analogWrite(bright,0);
  digitalWrite(led,0);
  dht.begin();
  timeClient.begin();
  client.setCallback(callback);
}
// Hàm kết nối wifi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client")) {
    //if (client.connect("ESP8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      client.subscribe("home/switch");
      client.subscribe("home/brightness");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
  }
}
void callback(String topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();
    if(topic=="home/switch"){
      Serial.print("Changing Light to ");
      if(messageTemp == "ON"){
        digitalWrite(led,1);
        Serial.print("On");
      }
      else if(messageTemp == "OFF"){
        digitalWrite(led,0);
        Serial.print("Off");
      }
    }
    if(topic=="home/brightness"){
      int value = messageTemp.toInt();
      analogWrite(bright,value);
    }
    Serial.println();
}

void loop() {
 
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  timeClient.update();
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  if (now - lastMeasure > 1000) {
    lastMeasure = now;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("\nFailed to read from DHT sensor!");
      return;
    }

    formattedDate = timeClient.getFormattedDate();
    // Extract date
    int splitT = formattedDate.indexOf("T");
    dayStamp = formattedDate.substring(0, splitT);
    int day = dayStamp.length() + 1;
    char day_array[day];
    dayStamp.toCharArray(day_array,day);
    // Extract time
    timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
    int tim = timeStamp.length() + 1;
    char time_array[tim];
    timeStamp.toCharArray(time_array,tim);
    
    data["SensorID"] = "DHT11";
//   data["Temperature"] = t ;
//    data["Humidity"] = h;
    data["Temperature"] = random(20,38);
    data["Humidity"] = random(45,90);
    data["Time"] = timeStamp;
    char payload[256];
    data.printTo(payload, sizeof(payload));
    String strPayload = String(payload);
    Serial.print("Format data: ");
    Serial.println(strPayload);
    client.publish("home/sensors", strPayload.c_str());
  }
}
