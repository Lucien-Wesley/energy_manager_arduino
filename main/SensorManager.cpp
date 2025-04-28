
#include "SensorManager.h"
#include "APIClient.h"
#include "DeviceManager.h"

float voltage = 0;
float current = 0;
float energy = 0;
float totalEnergy = 0;

ZMPT101B voltageSensor(ZMPT_PIN, 50.0);
ACS712  ACS(ACS_PIN, 3.3, 4095, 185);

void setupVoltageSensor() {
  voltageSensor.setSensitivity(SENSITIVITY);
}

float measureVoltage() {
  float raw = voltageSensor.getRmsVoltage();
  return raw;
}

float measureCurrent() {
  float raw = ACS.mA_AC();
  float result = raw / 1000;
  if (result < 0) {
    return 0;
  }
  return result;
}

void measureAndSendData() {
  voltage = measureVoltage();
  current = measureCurrent();
  energy = voltage * current * (MEASURE_INTERVAL / 1000.0 / 3600.0);
  totalEnergy += energy;
  estimateDeviceConsumption();
  sendDataToAPI();
}
