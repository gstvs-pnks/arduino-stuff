#include "functions.h"

#define PIN_TX 7
#define PIN_RX 8

SoftwareSerial mySerial(PIN_RX, PIN_TX);
DFRobot_SIM7000 sim7000(&mySerial);

const int AIN = A5; 
int sensorValue = 0;
int volts = 0;

const int ignitionPIN = 6;
bool ignition = false;

void bootUp(){

  Serial.println("Modem turning on...");
    if(sim7000.turnON()){
    Serial.println("Modem ON!");
    }
  
  Serial.println("Setting baudrate to 19200...");
    while(1){
      if(sim7000.setBaudRate(19200)){
        Serial.println("Baudrate set!");
        break;
      }
      else{
        Serial.println("ERROR! Baudrate not set!");
        delay(1000);
      }
    }

  Serial.println("Checking SIM card...");
    if(sim7000.checkSIMStatus()){
      Serial.println("SIM card READY");
    }
    else{
      Serial.println("SIM card ERROR");
      while(1);
    }

  Serial.println("Init positioning function...");
    while(1){
    	if(sim7000.initPos()){
        Serial.println("Positioning function initialized!");
        break;
      }else{
        Serial.println("Failed to init positioning function!");
        delay(1000);
      }
    }
}

//simply reads the ignition status
int ign_stat(){
  
  ignition = digitalRead(ignitionPIN);

  return ignition; 

}
//converts analog signal to milivolts
int voltage(){
 
  sensorValue = analogRead(AIN);
  volts = (sensorValue * (5.0 / 1023.0)) * 1000;

  return volts; 

}
//two blinks
void statusLED(){
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(333);  
  digitalWrite(LED_BUILTIN, LOW);
  delay(333);  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(333);  
  digitalWrite(LED_BUILTIN, LOW);

}
//collects info in one string
String packet(){
  
  String message = String("LAT:") + sim7000.getLatitude() + String(";LON:") + sim7000.getLongitude() + String(";IGN:") + String(ign_stat()) + String(";AIN:") + String(voltage());

  return message; 

}
//serial.print + status led
void printPack(){

  statusLED();
  Serial.println(packet());

}