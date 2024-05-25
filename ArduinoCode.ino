
#include <dht11.h>
#include "MAX30100_PulseOximeter.h"
#include<Wire.h>
#include <SoftwareSerial.h>
#define REPORTING_PERIOD_MS  3000
PulseOximeter pox;
SoftwareSerial B(11,10); // RX, TX

#define DHT11PIN 2
dht11 DHT11;
uint32_t lastReportTime = 0;
void onBeatDetected() {
   // Serial.println("Beat!");
}

void setup() {
  Serial.begin(9600); // Initialize hardware serial for debugging
  B.begin(9600);      // Initialize SoftwareSerial
  
  if (!pox.begin()) {
        Serial.println("Could not find a valid MAX30100 sensor, check wiring!");
        while (1);
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);
  
            // Initialize DHT sensor
  Serial.println("Setup complete. Waiting for sensor to stabilize...");
}

void loop() {
  pox.update();
 int chk = DHT11.read(DHT11PIN);


   if (millis() - lastReportTime > REPORTING_PERIOD_MS)
    {
        lastReportTime = millis();  
        
//     + String(dht.readTemperature())
  if (pox.getHeartRate() > 0 && pox.getSpO2() > 0) {
 String output =String(int(pox.getHeartRate())) + " "+ String(pox.getSpO2())+" "+String((float)DHT11.temperature, 2);  ;
            Serial.println(output);
            B.println(output);
            

  }else{
    String output = "-1 -1 -1 "  ;
            Serial.println(output);
            B.println(output);
    }
     lastReportTime = millis();
    } 


}






/*

#include <dht11.h>
#define DHT11PIN 2

dht11 DHT11;

void  setup()
{
  Serial.begin(9600);
 
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);

  delay(2000);

}

*/
