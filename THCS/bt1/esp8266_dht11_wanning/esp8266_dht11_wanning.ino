#include "DHT.h"
#define DHTPIN D7
#define DHTTYPE DHT11
#define COI D2
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(COI, OUTPUT);
}

void loop() {
  delay(2000);
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
  Serial.println(" *C ");

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
