
#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <Arduino.h>
#include <vector>

struct Appareil {
  int id;
  String adresseNRF;
  int state;
};

struct RelayCommand {
  byte relayIndex; // 0 à 5
  byte state;      // 0 = OFF, 1 = ON
};

extern RelayCommand cmd;

extern std::vector<Appareil> appareils;
#define DEVICE_CHECK_INTERVAL 5000

void initNRF24();
void handleCommand(String payload);
void syncDevices();
void estimateDeviceConsumption();

#endif
