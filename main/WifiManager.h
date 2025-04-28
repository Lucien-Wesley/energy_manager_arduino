
#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

extern String WIFI_SSID;
extern String WIFI_PASS;
extern String macAddress;
extern bool wifiConfigured;

void setWiFiCredentials(String ssid, String pass);
void connectToWiFi();
void initWiFi();

#endif
