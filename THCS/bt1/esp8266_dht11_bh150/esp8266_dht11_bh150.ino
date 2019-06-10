#include "DHT.h"
#define DHTPIN D7
#define DHTTYPE DHT11
#define COI D2
#define LED D1
int cambien = D0;// khai báo chân digital 4 cho cảm biến
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(cambien,INPUT);
  pinMode(COI,OUTPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  Serial.println("DHTxx and BH1750 test!");
  dht.begin();
}
void readDHT11(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C\t");
  if (t >= 25)
  {
    digitalWrite(COI, HIGH);
    delay(500);
    digitalWrite(COI, LOW);
    delay(500);
  }
  else
    digitalWrite(COI, LOW);  
}
void readBH150(){
  int value = digitalRead(cambien); 
  Serial.print("Light: ");
  Serial.println(value);//xuất giá trị 
  if(value == 1)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);
}
void loop() {
  delay(1000);
  readDHT11();
  readBH150();
}
