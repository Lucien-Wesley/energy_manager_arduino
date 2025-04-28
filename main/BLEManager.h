#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

void initBLE();

// 🆕 Ajout de la déclaration de la fonction d'envoi de données
void sendSensorData(float voltage, float current, float energy);

#endif
