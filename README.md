## ESP_DoubleResetDetector

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector)

This library is based on, modified, bug-fixed and improved from [`DataCute`] (https://github.com/datacute/DoubleResetDetector) to add support for ESP32.
 
Using this library to detect a double reset, using

1. RTC Memory, EEPROM or SPIFFS for ESP8266
2. EEPROM and SPIFFS for ESP32.

It is tested and working with 
1. The `ESP8266` Arduino platform with a recent stable release [`ESP8266 Core 2.6.2 or newer`] (https://github.com/esp8266/Arduino)
2. The `ESP32` Arduino platform with a recent stable release [`ESP32 Core 1.0.4 or newer`] (https://github.com/espressif/arduino-esp32)

### Releases
#### New in v1.0.1

1. Add EEPROM and SPIFFS support, besides RTC memory, for ESP8266
2. Add SPIFFS support, besides EEPROM, for ESP32


### PURPOSE:

Detects a double reset so that an alternative start-up mode can be used. One example use is to allow re-configuration of a device's wifi credentials.

