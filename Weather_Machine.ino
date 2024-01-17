// Necessary libraries
#include <Wire.h>              // Library for I2C communication
#include <Adafruit_BMP085.h>   // Library for BMP085 sensor
#include <SoftwareSerial.h>    // Library for software serial communication
#include <ArduinoBlue.h>       // Library for Bluetooth communication
#include <dht11.h>             // Library for DHT11 sensor

dht11 DHT11;                    // DHT11 sensor instance
#define dhtpin 2               // Pin for DHT11 sensor data
#define seaLevelPressure_hPa 1013.25   // Sea level pressure in hPa

const int BLUETOOTH_TX = 8;     // Bluetooth transmit pin
const int BLUETOOTH_RX = 7;     // Bluetooth receive pin

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);   // Software serial instance for Bluetooth communication
ArduinoBlue phone(bluetooth);                           // ArduinoBlue instance for Bluetooth messaging

Adafruit_BMP085 bmp;            // BMP085 sensor instance

bool introductoryMessageSent = false;  // Flag variable to track if introductory message has been sent

void setup() {
  bluetooth.begin(9600);        // Start Bluetooth communication at baud rate 9600
  bmp.begin();   // Initialize BMP085 sensor

  phone.sendMessage("Weather Machine created by Mr. C the Goat's Best Students Rishi & Vivek");
}

void loop() {
  if (!introductoryMessageSent) {
    // Send introductory message only once
    phone.sendMessage("Weather Machine created by Mr.C the Goat's Best Students Rishi & Vivek");
    introductoryMessageSent = true;  // Set the flag to indicate the message has been sent
  }

  delay(1000);  // Delay for 2 seconds
  
  float temperature = bmp.readTemperature();                   // Read temperature from BMP085 sensor
  float pressure = bmp.readPressure();                         // Read pressure from BMP085 sensor
  float altitude = bmp.readAltitude(seaLevelPressure_hPa);     // Read altitude from BMP085 sensor

  DHT11.read(dhtpin);                // Read data from DHT11 sensor
  int humidity = DHT11.humidity;     // Get humidity reading from DHT11 sensor
  int temp = (float)DHT11.temperature;  // Get temperature reading from DHT11 sensor

  // Send sensor data as a message through Bluetooth
  phone.sendMessage("Humidity: " + String(humidity) + "%\n" +
                    "Temperature: " + String(temperature-7) + " Degrees Celsius" + "\n" +
                    "Pressure: " + String(pressure/3386) + " inHg" + "\n" +
                    "Altitude: 218.0 meters");
}
