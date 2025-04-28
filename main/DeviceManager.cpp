
#include "DeviceManager.h"
#include "WifiManager.h"
#include "SensorManager.h"
#include <nRF24L01.h>
#include <RF24.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

std::vector<Appareil> appareils;
RF24 radio(26, 27); // CE, CSN
const byte address[6] = "00001";

void initNRF24() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.stopListening();
}

void handleCommand(String payload) {
  DynamicJsonDocument doc(256);
  deserializeJson(doc, payload);
  //Serial.println(payload);
  int id = doc["id"];
  int state = doc["state"];

  RelayCommand cmd;
  

  //for (auto &app : appareils) {
  //  if (app.id == id) {
  //app.state = state;

  int xid = payload.substring(5,6).toInt();
  int xstate = payload.substring(15).toInt();
  
  cmd.relayIndex = xid-1;
  cmd.state = xstate;

  Serial.println(xid);
  Serial.println(xstate);

  bool ok = radio.write(&cmd, sizeof(cmd));

  if (ok) {
    Serial.print("Commande envoyée → relais ");
    Serial.print(xid);
    Serial.print(xstate == 1 ? " ON" : " OFF");
    Serial.println();
  } else {
    Serial.println("❌ Échec d’envoi.");
  }
  //    break;
  //  }
  //}

  if (wifiConfigured) {
    HTTPClient http;
    http.begin("http://example.com/api/command");
    http.addHeader("Content-Type", "application/json");
    String json;
    serializeJson(doc, json);
    http.POST(json);
    http.end();
  }
}

void syncDevices() {
  if (!wifiConfigured) return;

  HTTPClient http;
  http.begin("http://example.com/api/devices?mac=" + macAddress);
  int httpCode = http.GET();
  if (httpCode == 200) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, http.getStream());
    appareils.clear();
    for (JsonObject item : doc.as<JsonArray>()) {
      Appareil a;
      a.id = item["id"];
      a.adresseNRF = String(item["nrf_address"].as<const char*>());
      a.state = item["state"];
      appareils.push_back(a);
    }
  }
  http.end();
}

void estimateDeviceConsumption() {
  int nbActifs = 0;
  for (auto &app : appareils) if (app.state == 1) nbActifs++;
  if (nbActifs == 0) return;
  float part = 0;
  for (auto &app : appareils) {
    if (app.state == 1) {
      Serial.printf("Appareil %d -> conso estimée: %.2fA\n", app.id, part);
    }
  }
}
