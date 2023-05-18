#include <DHT.h>
#include <DHT_U.h>
#include "EspMQTTClient.h"

EspMQTTClient client(
  "MULTI_GUEST",
  "guest1357",
  "70.12.107.68",  // MQTT Broker server ip
  "MQTTUsername",   // Can be omitted if not needed
  "MQTTPassword",   // Can be omitted if not needed
  "client_bm",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

// Light
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
const int ledBlue = 16;
int light_state = 0;
int light_val = 0;

// DHT11
#define DHTPIN 13
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  
  // light
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledBlue, ledChannel);

  // DHT11
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  client.publish("home/livingroom/", "get");

  client.subscribe("home/livingroom/light", [](const String & payload) {
    if(payload == "ON") light_state = 1;
    else light_state = 0;
  });

  client.subscribe("home/livingroom/light/bright", [](const String & payload) {
    light_val = payload.toInt();
  });

  client.subscribe("home/livingroom", [](const String & payload) {
    if(payload=="get") {
      sensors_event_t event;
      dht.temperature().getEvent(&event);
      double temp = event.temperature;
      client.publish("home/livingroom/temperature", String(temp));

      dht.humidity().getEvent(&event);
      double humid = event.relative_humidity / 100;
      client.publish("home/livingroom/humidity", String(humid));

      int uncomfortable = (1.8 * temp) - (0.55 * (1 - humid) * (1.8 * temp - 26)) + 32;
      client.publish("home/livingroom/uncomfortable", String(uncomfortable));
    }
  });
}

void loop()
{
  client.loop();

  if(light_state) ledcWrite(ledChannel, light_val);
  else ledcWrite(ledChannel, 0);

  delay(10);
}
