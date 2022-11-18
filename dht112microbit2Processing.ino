#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600); 
  dht.begin();
}

void loop() {

  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo al leer el sensor DHT11");
    return;
  }
// Únicamente enviar a Processing las variables t y h 

 
Serial.print("Temperatura=");
Serial.print(t);
Serial.print("&Humedad=");
Serial.println(h);
 
}