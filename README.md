# -Monitoring-and-The-Study-of-Sensor-s-

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sensor Monitoring Project
// 
// This project is designed to monitor environmental conditions such as temperature, humidity, voltage, 
// and current in real-time. The data is displayed on an LCD and can be monitored remotely via the 
// Blynk IoT platform. The system also includes alarm features using LEDs and a buzzer to warn when 
// preset thresholds are exceeded.
// 
// Components:
// 1. ESP32: Central controller, handling sensor data and communication with Blynk.
// 2. DHT11: Temperature and humidity sensor.
// 3. ACS712: Current sensor for monitoring electrical current.
// 4. Voltage Sensor: Measures voltage levels in the system.
// 5. LCD Display: For local real-time display of sensor values.
// 6. Blynk Platform: For remote monitoring and control via a smartphone.
// 7. Alarm System: Uses LEDs and a buzzer to alert when sensor readings exceed thresholds.
//
// Features:
// - Real-time temperature and humidity monitoring with alarms for high temperatures.
// - Voltage monitoring with an alarm system if voltage exceeds the set threshold.
// - Current monitoring with data displayed on the LCD and sent to Blynk.
// - Remote monitoring via the Blynk app using virtual pins to display sensor data.
// 
// Future Improvements:
// - Additional sensors for more comprehensive monitoring.
// - Data logging for historical analysis.
// - More complex alarm conditions (e.g., humidity, current).
////////////////////////////////////////////////////////////////////////////////////////////////////////
