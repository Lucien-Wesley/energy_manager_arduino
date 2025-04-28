
#include "APIClient.h"
#include "WifiManager.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "SensorManager.h"

const String API_BASE = "hhttp://192.168.1.66:5000";

void sendDataToAPI() {
  if (!wifiConfigured) return;

  HTTPClient http;
  http.begin(API_BASE + "/consumption");
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument doc(512);
  doc["id"] = macAddress;
  //doc["voltage"] = voltage;
  //doc["current"] = current;
  doc["consumption"] = energy;

  String payload;
  serializeJson(doc, payload);
  http.POST(payload);
  http.end();
}
