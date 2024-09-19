////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * SENSOR PROJECT OVERVIEW:
 * This project involves using an ESP32 to monitor temperature, humidity, voltage, and current using various sensors (DHT11 for temperature/humidity, ACS712 for current).
 * The data is displayed on an LCD screen and sent to the Blynk app for remote monitoring. Additionally, alarms (LEDs and buzzer) are triggered when sensor readings 
 * exceed certain thresholds. 
 *
 * Steps involved:
 * 1. Initialize WiFi connection using Blynk credentials.
 * 2. Set up the sensors and LCD display.
 * 3. Read and process data from the temperature/humidity sensor (DHT11), voltage sensor, and current sensor (ACS712).
 * 4. Display the sensor data on the LCD screen.
 * 5. Trigger alarms if readings exceed predefined thresholds (e.g., temperature > 42°C, voltage > 4V).
 * 6. Send the processed data to the Blynk app for remote access and monitoring.
 * 7. Continuously loop to update sensor readings and alarms.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Blynk Template ID and Authentication Token for connecting the ESP32 to the Blynk platform.
// Make sure to update these with your own Blynk credentials if needed.
#define BLYNK_TEMPLATE_ID "TMPL3Lkw3nIoQ"
#define BLYNK_TEMPLATE_NAME "SENSOR PROJECT"
#define BLYNK_AUTH_TOKEN "KNkgV23jpnq3-ge6Cyl4m1V1SGf-Vxh_"

////////////////////////////////////////////////////////////////////////////////////////////////////////

// WiFi credentials - update with your own WiFi network name and password to connect the ESP32 to the internet.
char ssid[] = "Mi A3";        // Your WiFi name
char pass[] = "12345678";     // Your WiFi password

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Include the necessary libraries for the project. These libraries are required for the following functionalities:
// - WiFi connectivity (ESP32 to internet/Blynk).
// - Blynk connection (for remote monitoring and control).
// - LCD display control (for local data display).
// - DHT11 sensor (for temperature and humidity readings).
// - ACS712 sensor (for current measurements).
#define BLYNK_PRINT Serial   // Library used to print Blynk-related info on Serial Monitor
#include <WiFi.h>            // Library for WiFi connectivity for ESP32
#include <WiFiClient.h>  
#include <BlynkSimpleEsp32.h> // Library for integrating Blynk with ESP32
#include <LiquidCrystal_I2C.h> // Library for controlling I2C LCD display
#include <DHT.h>              // Library for DHT sensor (temperature and humidity)

#include "ACS712.h"           // Library for ACS712 current sensor

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Blynk Timer: Manages the interval at which data is sent to Blynk (1 second in this case).
BlynkTimer timer;

// Define the pin for the DHT11 sensor and specify the type of sensor used (DHT11 in this case).
#define DHTPIN 4              // Pin DHT11 is connected to on ESP32 (D2)
#define DHTTYPE DHT11         // Type of DHT sensor used (DHT11)
DHT dht(DHTPIN, DHTTYPE);     // Initialize DHT sensor

// Initialize the ACS712 current sensor. ACS712_05B refers to the 5A version of the sensor, and it's connected to pin 35 on the ESP32.
ACS712 sensor(ACS712_05B, 35);

// Initialize the LCD display with its I2C address (0x27), and specify it has 16 columns and 2 rows.
LiquidCrystal_I2C lcd(0x27, 16, 2);

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Define pins for the alarm system. The alarms include two LEDs and a buzzer:
// - ledPin: Pin 16 for an LED (turns on when temperature exceeds threshold).
// - ledPin1: Pin 17 for another LED (turns on when voltage exceeds threshold).
// - buzz: Pin 18 for a buzzer (sounds when any alarm is triggered).
int sensorValue;
const int ledPin = 16;  // LED for temperature alarm
const int ledPin1 = 17; // LED for voltage alarm
const int buzz = 18;    // Buzzer for alarms

////////////////////////////////////////////////////////////////////////////////////////////////////////

// The setup function runs once at the beginning when the ESP32 starts up. It initializes the sensors, LCD display, WiFi connection, and Blynk.
// - It also sets up the pins for the LEDs and buzzer.
void setup() {
    Serial.begin(115200);     // Start serial communication at 115200 baud rate
    dht.begin();              // Initialize the DHT11 sensor
    sensor.calibrate();       // Calibrate the ACS712 current sensor

    // Set up the pins for the LEDs and buzzer as outputs, and ensure they are initially turned off.
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    pinMode(ledPin1, OUTPUT);
    digitalWrite(ledPin1, LOW);
    pinMode(buzz, OUTPUT);
    digitalWrite(buzz, LOW);

    // Initialize and clear the LCD display.
    lcd.init();  
    lcd.backlight();  
    lcd.clear();  

    // Set a timer to run the sendSensor function every second (1000 milliseconds).
    timer.setInterval(1000L, sendSensor);

    // Start the Blynk connection using the authentication token and WiFi credentials defined earlier.
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
