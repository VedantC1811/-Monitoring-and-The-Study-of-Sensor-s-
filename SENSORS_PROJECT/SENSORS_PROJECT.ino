////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BLYNK_TEMPLATE_ID "TMPL3Lkw3nIoQ"
#define BLYNK_TEMPLATE_NAME "SENSOR PROJECT"
#define BLYNK_AUTH_TOKEN "KNkgV23jpnq3-ge6Cyl4m1V1SGf-Vxh_"
////////////////////////////////////////////////////////////////////////////////////////////////////////

// Make sure to Put correct name and credentials //

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Comment out these lines as we won't be needing them
 char ssid[] = "Mi A3";         // put your wifi name here same exactly
 char pass[] = "12345678";        // put your wifi password here

////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BLYNK_PRINT Serial   // library link in description
#include <WiFi.h>     // library link in description
#include <WiFiClient.h>  
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#include "ACS712.h"

BlynkTimer timer;
#define DHTPIN 4 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
ACS712 sensor(ACS712_05B, 35);
LiquidCrystal_I2C lcd(0x27, 16, 2);



 

int sensorValue;
const int ledPin = 16; // Alarm LED pin
const int ledPin1 = 17; // Alarm LED pin
const int buzz = 18; // Alarm LED pin




void setup() {
    Serial.begin(115200);
    dht.begin();
    sensor.calibrate();

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    pinMode(ledPin1, OUTPUT);
    digitalWrite(ledPin1, LOW);
    pinMode(buzz, OUTPUT);
    digitalWrite(buzz, LOW);

    lcd.init();
    lcd.backlight();
    lcd.clear();

 timer.setInterval(1000L, sendSensor);

  
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
   

  
    delay(1000);
}


// TEMPERATURE AND HUMIDITY SENSOR(DHT11) 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sendSensor() {
// Your loop code remains the same
     float t = dht.readTemperature(); // Read temperature from DHT sensor
    
    if (!isnan(t)) { // Check if the temperature reading is valid
        
        Serial.print("Temperature: ");
        Serial.println(t);
    } else {
        Serial.println("Failed to read temperature from sensor");
    }

    if (t >= 42) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Turn on alarm");
    digitalWrite(buzz, HIGH);
    delay(50);
     digitalWrite(buzz, LOW);
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Turn off alarm");
  }

   lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// VOLTAGE SENSOR 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Read voltage from  sensor
sensorValue = analogRead(32);
    Serial.println(sensorValue);
  float volt = sensorValue * (5.0 / 5600.0);
  Serial.println("Voltage : ");
  Serial.println(volt);
  float Vin = volt * 2;
  Serial.println("Voltage : ");
  Serial.println(Vin);
  if (Vin >= 4) {
    digitalWrite(ledPin1, HIGH);
    Serial.println("Turn on alarm");
    digitalWrite(buzz, HIGH);
    delay(50);
     digitalWrite(buzz, LOW);
    
  } else {
    digitalWrite(ledPin1, LOW);
    Serial.println("Turn off alarm");
   
  }

   lcd.setCursor(9, 1);
  lcd.print("V:");
  lcd.print(Vin);
  lcd.print("V");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// CURRENT SENSOR CODE(ACS712)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Read current from ACS712 sensor
float current = sensor.getCurrentAC();
if (current < 0.50){ 
    current = 0;
}
    Serial.print("Current: ");
    Serial.println(current);
    

 // Display values on LCD
  lcd.setCursor(0, 1);
  lcd.print("C:");
  lcd.print(current);
  lcd.print("A");
  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SENDING 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Send temperature to Blynk app
        Blynk.virtualWrite(V0, t);
  // Send current to Blynk app
Blynk.virtualWrite(V1, current);
Blynk.virtualWrite(V2,Vin );
  
 
delay(1000);
}



void loop() {
   
Blynk.run();
timer.run();
}
