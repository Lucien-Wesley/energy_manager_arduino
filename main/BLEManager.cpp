#include "BLEManager.h"
#include "WifiManager.h"
#include "DeviceManager.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define BLE_SERVICE_UUID "12345678-1234-5678-1234-56789abcdef0"
#define BLE_CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-abcdef123456"

// 🔁 On rend la caractéristique globale pour l’utiliser ailleurs
BLECharacteristic *pCharacteristic = nullptr;

class MyBLECallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) override {
    auto rxValue = pCharacteristic->getValue();
    if (!rxValue.isEmpty()) {
      String data = String(rxValue.c_str());

      if (data.startsWith("CMD:")) {
        handleCommand(data.substring(4));
      } else if (data.startsWith("WIFI:")) {
        Serial.println(data);
        int sep = data.indexOf("|");
        setWiFiCredentials(data.substring(5, sep), data.substring(sep + 1));
        connectToWiFi();
      }
    }
  }
};

void initBLE() {
  BLEDevice::init("Energy-Manager");
  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(BLE_SERVICE_UUID);

  // 🆕 On ajoute aussi la propriété NOTIFY
  pCharacteristic = service->createCharacteristic(
    BLE_CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->setCallbacks(new MyBLECallbacks());
  service->start();
  BLEDevice::getAdvertising()->start();
}

// ✅ Fonction pour envoyer tension, courant et énergie via BLE
void sendSensorData(float voltage, float current, float energy) {
  if (pCharacteristic != nullptr) {
    String json = "{\"v\": " + String(voltage, 2) + "}";
    pCharacteristic->setValue(json.c_str());
    pCharacteristic->notify();
    //Serial.println("📤 Données envoyées via BLE : " + json);
    json = "{\"c\": " + String(current, 2) + "}";
    pCharacteristic->setValue(json.c_str());
    pCharacteristic->notify();
    //Serial.println("📤 Données envoyées via BLE : " + json);
    json = "{\"e\": " + String(energy, 2) + "}";
    pCharacteristic->setValue(json.c_str());
    pCharacteristic->notify();
    //Serial.println("📤 Données envoyées via BLE : " + json);
  }
}
