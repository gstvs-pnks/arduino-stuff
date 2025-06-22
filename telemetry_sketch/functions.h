#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include <DFRobot_SIM7000.h>
#include <SoftwareSerial.h>

extern SoftwareSerial mySerial;
extern DFRobot_SIM7000 sim7000;

extern const int AIN; 
extern int sensorValue;
extern int volts;

extern const int ignitionPIN;
extern bool ignition;

void bootUp();
int ign_stat();
int voltage();
void statusLED();
String packet();
void printPack();

#endif