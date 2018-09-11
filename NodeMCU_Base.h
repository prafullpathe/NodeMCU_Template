/* NodeMCU_Base.h
* Node MCU Base
*   Dx nomenclature is defined within esp8266 core logic.  It can be used here as required
  NODE MCU Pinout
  D0 = GPIO16 (SPARE)
  D1 = GPIO5 (OLED - SCL)
  D2 = GPIO4 (OLED - SDA)
  D3 = GPIO0 (DS18B20)    -  CAUTION! This pin is reset the NodeMCU during program download
  D4 = GPIO2 (DO NOT USE)
  D5 = GPIO14 (Spare)
  D6 = GPIO12 (Spare)
  D7 = GPIO13 (Spare)
  D8 = GPIO15 (DO NOT USE) - must not be used with pullup resistor or logic will not download
  
  A0 = A0 (AI#1)
*/

#ifndef NODEMCU_BASE_H
#define NODEMCU_BASE_H

#include "Arduino.h"
#include "NodeMCU_Base.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <PCF8574.h>
#include <ESP8266WiFi.h>

#define GPIO_DS18B20  D3    // Define the pin used for the DS18B20 temperature measurement
#define GPIO_I2C_SCL  D1    // Define the pin used for the I2C SCL communication protocol 
#define GPIO_I2C_SDA  D2     // Define the pin used for the I2C SDA communication protocol     
#define GPIO_RDO1     P0     // Define the pin used for remote discrete output 1
#define GPIO_RDO2     P1     // Define the pin used for remote discrete output 2
#define GPIO_RDI1     P2     // Define the pin used for remote discrete input 1
#define GPIO_RDI2     P3     // Define the pin used for remote discrete input 1
#define GPIO_RDI3     P4     // Define the pin used for remote discrete input 1
#define GPIO_RDI4     P5     // Define the pin used for remote discrete input 1
#define GPIO_RDI5     P6     // Define the pin used for remote discrete input 1
#define GPIO_RDI6     P7     // Define the pin used for remote discrete input 1


class NodeMCU_Base
{
 
   public:
        NodeMCU_Base(int value);
        bool begin();

        // DS18B20 functions
        float readTemperature(); //-> This would read the temperature from the local DS18B20
        
        //PCF8574 functions
        void digitalWrite(int pin, int value);
        int digitalRead(int pin);

        // Wifi functions

        // MQTT functions
        
    private:
        // DS18B20
        bool setupDS18B20();
        double DS18B20_temp;

        // PCF8574
        bool setupPCF8574(); 
        
        // Wifi
        bool setupWifi();
};

#endif
