/* Temperature monitoring system for ESP32 
 * https://srituhobby.com
 */

#define BLYNK_PRINT Serial
#include <WiFi.h>
// #include <ESP32WiFi.h>
// #include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(4, DHT11); //(sensor pin, sensor type) - GPIO4 corresponds to D3 on ESP8266

// char auth[] = ""; // Enter the Auth code sent by Blynk
char ssid[] = "";  // Enter your WiFi Name
char pass[] = "";  // Enter your WiFi Password

BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("Humi : ");
  lcd.print(h);

  // Blynk.virtualWrite(V0, t);
  // Blynk.virtualWrite(V1, h);
}

void setup() {
  Wire.begin(21, 22);  // ESP32 default I2C pins (SDA = 21, SCL = 22)
  lcd.init();
  lcd.backlight();
  // Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, sendSensor);
}

void loop() {
  // Blynk.run();
  timer.run();
}
