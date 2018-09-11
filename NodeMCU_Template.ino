/*
 * Convert to using a NodeMCU from Anrduino UNO
 * Uses PCF8574 I2C I/O expander to add 8 additional DIO
 * Uses 1 Analogue Input on A0
 */

#include <NodeMCU_Base.h>
NodeMCU_Base base (4);

#include <ESP8266WiFi.h>
const char* ssid2 = "RedBear";
const char* password2 = "VLgregRy4h";

int in1 = 0;
int in2 = 0;

void flashOutputs(int times)
{
  for (int i = 0; i < times; i++){
    base.digitalWrite(GPIO_RDO1, HIGH);
    delay (500);
    base.digitalWrite(GPIO_RDO2, HIGH);
    delay (500);
    base.digitalWrite(GPIO_RDO1, LOW);
    delay (500);
    base.digitalWrite(GPIO_RDO2, LOW);
    delay (500);
  }

}

void setup() {
  Serial.begin(115200);
  Serial.println("setup called...");
  
  bool success = base.begin();
  if (success) {
    Serial.println ("NodeMCU Base setup successfully!");
  } else {
    Serial.println ("NodeMCU Base setup failed!");
  }
  
  float t = base.readTemperature();
  Serial.print("Read: "); Serial.println(t);

  flashOutputs(1);
  Serial.println("Setup complete!");

  base.digitalRead(GPIO_RDI2);

  WiFi.begin(ssid2, password2);
  delay (250);
  if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid2, password2);
        delay(250);
    }
  Serial.println(WiFi.localIP());
}


void loop() {

  //flashOutputs(2);
  in1 = base.digitalRead(GPIO_RDI1);
  in2 = base.digitalRead(GPIO_RDI2);
  /*Serial.print("IN1: ");
  Serial.print(in1);
  Serial.print("\t ");
  Serial.print("IN2: ");
  Serial.println(in2);*/
  
  if (in1 > 0){
    base.digitalWrite(GPIO_RDO1,HIGH);
  }else{
    base.digitalWrite(GPIO_RDO1,LOW);}
  
  if (in2 > 0){
    base.digitalWrite(GPIO_RDO2,HIGH);
  }else{
    base.digitalWrite(GPIO_RDO2,LOW);}
    
  //Serial.println(base.readTemperature());
}


