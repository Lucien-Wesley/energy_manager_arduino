#include <Arduino.h>
#include "BLEManager.h"
#include "WifiManager.h"
#include "SensorManager.h"
#include "APIClient.h"
#include "DeviceManager.h"

unsigned long lastMeasure = 0;
unsigned long lastDeviceCheck = 0;

void setup() {
  Serial.begin(115200);
  initWiFi();
  setupVoltageSensor(); 
  initBLE();
  initNRF24();
}

void loop() {
  unsigned long now = millis();

  if (now - lastMeasure > MEASURE_INTERVAL) {
    measureAndSendData();
    sendSensorData(voltage, current, totalEnergy);
    lastMeasure = now;
  }

  if (now - lastDeviceCheck > DEVICE_CHECK_INTERVAL) {
    syncDevices();
    lastDeviceCheck = now;
  }
}
