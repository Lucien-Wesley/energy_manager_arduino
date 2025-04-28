
#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <ZMPT101B.h>
#include <ACS712.h>

#define ZMPT_PIN 34
#define ACS_PIN 35
#define MEASURE_INTERVAL 10000
#define SENSITIVITY 500.0f

extern float voltage, current, energy, totalEnergy;
extern ZMPT101B voltageSensor;
extern ACS712  ACS;

void measureAndSendData();
void setupVoltageSensor();
float measureVoltage();


#endif

