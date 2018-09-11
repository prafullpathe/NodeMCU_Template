#include "Arduino.h"
#include "NodeMCU_Base.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <PCF8574.h>
#include <ESP8266WiFi.h>

// ==================== Setup DS18B20 =========================
// Setup a OneWire instance to communicate with any OneWire device
//OneWire oneWire(GPIO_DS18B20);
OneWire oneWire(GPIO_DS18B20);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


// ==================== Setup PCF8574 =========================
int pcf8574Address = 0x20;
//PCF8574 pcf8574(pcf8574Address);
PCF8574 pcf8574(0x20);

// ==================== Setup WiFi  =========================
WiFiClient espClient;
// Update these with values suitable for your network.
const char* ssid = "RedBear";
const char* password = "VLgregRy4h";
//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // This probably isn't required    // Try to replace with DS18B20 MAC
bool wifiConnected = false;    // use connected status in other sections of code (disable MQTT if Wifi disconnected)


NodeMCU_Base::NodeMCU_Base(int value)
{

}

bool NodeMCU_Base::begin()
{
    bool ds18B20Configured = setupDS18B20();

    bool pcf8574Configured = setupPCF8574();

//    bool wifiConfigured = setupWifi();

    return ds18B20Configured && pcf8574Configured /* && wifiConfigured*/;
}

float NodeMCU_Base::readTemperature()
{
    // read DS18B20 temperature sensor at index 0 (first sensor)
    sensors.requestTemperatures();  
    DS18B20_temp = sensors.getTempCByIndex(0);
    delay (10);   // small delay to ensure temperature is set correctly
    return DS18B20_temp;
}

void NodeMCU_Base::digitalWrite(int pin, int value)
{
    pcf8574.digitalWrite(pin, value);
}

int NodeMCU_Base::digitalRead(int pin)
{
    pcf8574.readBuffer();
    return pcf8574.digitalRead(pin);
}

/*int NodeMCU_Base::digitalReadAll()
{
    PCF8574::DigitalInput di = pcf8574.digitalReadAll();

    return pcf8574.digitalRead(pin);
}*/

// Private functions

bool NodeMCU_Base::setupDS18B20()
{
    // Start measuring the DS18B20 sensor
    sensors.begin();
    Serial.println("Begin scanning DS18B20 sensor...");
    if (sensors.getDS18Count() == 0) {
        Serial.println("DS18B20 setup failed!");
        return false;
    }
    return true;
}

bool NodeMCU_Base::setupPCF8574()
{
    Serial.print ("Looking for I2C Address: ");
    Serial.println(pcf8574Address);

    Wire.begin();
    Wire.beginTransmission(pcf8574Address);
    byte error = Wire.endTransmission();
    if (error != 0)
    {
        Serial.println("PCF8574 setup failed!");
        return false;
    }

    // Set pinMode to OUTPUT
    pcf8574.pinMode(P0, OUTPUT);
    pcf8574.pinMode(P1, OUTPUT);
    pcf8574.pinMode(P2, INPUT);
    pcf8574.pinMode(P3, INPUT);
    pcf8574.pinMode(P4, INPUT);
    pcf8574.pinMode(P5, INPUT);
const char* ssid = "RedBear";
const char* password = "VLgregRy4h";
    pcf8574.pinMode(P6, INPUT);
    pcf8574.pinMode(P7, INPUT);
    pcf8574.begin();

    return true;
}

bool NodeMCU_Base::setupWifi()
{
    // We start by connecting to a WiFi network
    Serial.print ("Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA); // <<< Station
    WiFi.begin(ssid, password);
//Serial.println(ssid);
//Serial.println(password);  
    // Try to connect 3 times with 250 msec in between each attempt
    for (int i =0; i < 3; i++)
    {
        if (WiFi.status() != WL_CONNECTED) 
        {
            WiFi.begin(ssid, password);
            Serial.print("Connect attempt #");
            Serial.println(i);
            delay(250);
        } 
        else 
        {
            wifiConnected = true;
            continue;
const char* ssid = "RedBear";
const char* password = "VLgregRy4h";
        }
    }

    if (wifiConnected)
    {
        Serial.print ("WiFi connected! IP address: ");
        Serial.println(WiFi.localIP());
    
    }
    else
    {
        Serial.print("Could not connect to ");
        Serial.println(ssid);
    }

    return wifiConnected;
}
