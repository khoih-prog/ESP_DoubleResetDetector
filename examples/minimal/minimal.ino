/****************************************************************************************************************************
   minimal.ino
   For ESP8266 / ESP32 boards

   ESP_DoubleResetDetector is a library for the ESP8266/Arduino platform
   to enable trigger configure mode by resetting ESP32 / ESP8266 twice.

   Forked from DataCute https://github.com/datacute/DoubleResetDetector

   Built by Khoi Hoang https://github.com/khoih-prog/ESP_DoubleResetDetector
   Licensed under MIT license
   Version: 1.0.2

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      15/12/2019 Initial coding
    1.0.1   K Hoang      30/12/2019 Now can use EEPROM or SPIFFS for both ESP8266 and ESP32. RTC still OK for ESP8266
    1.0.2   K Hoang      10/04/2020 Fix bug by left-over cpp file and in example.
 *****************************************************************************************************************************/

#include <ESP_DoubleResetDetector.h>

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);

#ifndef LED_BUILTIN
#define LED_BUILTIN       2         // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
#endif

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("DoubleResetDetector Example Program");
  Serial.println("-----------------------------------");

  if (drd.detectDoubleReset()) {
    Serial.println("Double Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.println("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void loop()
{
  // Call the double reset detector loop method every so often,
  // so that it can recognise when the timeout expires.
  // You can also call drd.stop() when you wish to no longer
  // consider the next reset as a double reset.
  drd.loop();
}
