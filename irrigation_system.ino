//Jorge Muñoz Rodenas
//IES Amparo Sanz (Albacete)
//2022

#include "DHTesp.h"
#include <WiFi.h>
#include <ThingSpeak.h>

#ifndef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP32 ONLY!)
#error Select ESP32 board.
#endif

DHTesp dht;

WiFiClient client;
const char* ssid     = "vodafone38D0";
const char* password = "NTVTYJFMMKVWZ4";

const char* myAPIKey = "LQ8USYIJNX2ZIEZZ";
unsigned long myChannel = 1941900;
float previous = millis();
#define dhtPin 32
#define soilHumPin 34
#define pinLED 0
void setup() {

  Serial.println();
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
  pinMode(pinLED, OUTPUT);
  Serial.begin(115200);
  // Initialize temperature sensor
  dht.setup(dhtPin, DHTesp::DHT22);
  Serial.println("DHT initiated");
  ThingSpeak.begin(client);

}

void loop() {

  TempAndHumidity newValues = dht.getTempAndHumidity();
  float tempC = newValues.temperature;
  float humidity = newValues.humidity;
  int soilHum = analogRead(soilHumPin);
  if (millis() - previous > 15000) { //smart delay 15 sec.
    if (dht.getStatus() != 0) {
      Serial.println("DHT22 error status: " + String(dht.getStatusString()));
    }
    else Serial.println(" T:" + String(tempC) + " H:" + String(humidity));
    Serial.println("Soil humidity: " + String(soilHum));
    if (soilHum > 3000) digitalWrite(pinLED, HIGH);
    else digitalWrite(pinLED, LOW);

    previous = millis();
  
    //Send data to ThingSpeak

    ThingSpeak.setField(1, tempC);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, soilHum);
    ThingSpeak.writeFields(myChannel, myAPIKey);
  }
}
