#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11
//#define ssid "bamlanat"
//#define password "chigooglecungbotay@123!!!"
const char* ssid     = "NhungKa";
const char* password = "nhungdaika";
// Thông tin về MQTT Broker
#define mqtt_server "m16.cloudmqtt.com" // Thay bằng địa chỉ IP 
#define mqtt_topic_pub "Test"   
#define mqtt_topic_sub "Test"
#define mqtt_user "lteqwnjb"    
#define mqtt_pwd "O_zUwzxs1rqM"

const uint16_t mqtt_port = 12155; //Port của MQTT


WiFiClient espClient;
PubSubClient client(espClient);

const int DHTPin3 = D5;       //Đọc dữ liệu từ DHT11 ở chân D7 trên mạch esp8266

long lastMsg = 0;
char msg[50];
int value = 0;
// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Thiet Lap cam bien DHT.
DHT dht(DHTPin3, DHTTYPE);

void setup() {
  Serial.begin(300);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  dht.begin();


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
// Hàm reconnect thực hiện kết nối lại khi mất kết nối với MQTT Broker
void reconnect() {
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("ESP8266Client",mqtt_user, mqtt_pwd)) {
      Serial.println("connected");
      // Khi kết nối sẽ publish thông báo
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      // ... và nhận lại thông tin này
      client.subscribe(mqtt_topic_sub);
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
  //Kiểm tra kết nối
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  // Publishes new temperature and humidity every 30 seconds
  if (now - lastMeasure > 1000) {
    lastMeasure = now;
    getAndSendTemperatureAndHumidityData();
  }
}

void getAndSendTemperatureAndHumidityData()
{
  Serial.println("Collecting temperature data.");
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  String temperature = String(t);
  String humidity = String(h);


  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"Temp\":"; payload += temperature; payload+=",";
  payload += "\"Hum\":"; payload += humidity; payload;
  payload += "}";

  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish( "Test", attributes );
  Serial.println( attributes );
  delay(5000);
}
