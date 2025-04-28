
#include "WifiManager.h"
#include <WiFi.h>

String WIFI_SSID = "";
String WIFI_PASS = "";
bool wifiConfigured = false;
String macAddress = "FC:E8:C0:74:DA:2A";

void setWiFiCredentials(String ssid, String pass) {
  WIFI_SSID = ssid;
  WIFI_PASS = pass;
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry++ < 20) {
    delay(500);
  }
  wifiConfigured = (WiFi.status() == WL_CONNECTED);
  //if (wifiConfigured) macAddress = WiFi.macAddress();
}

void initWiFi() {
  WiFi.disconnect();
  connectToWiFi();
}
