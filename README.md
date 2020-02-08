## ESP_DoubleResetDetector

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector)

This library is based on, modified, bug-fixed and improved from [`DataCute`](https://github.com/datacute/DoubleResetDetector) to add support for ESP32.
 
Using this library to detect a double reset, using

1. RTC Memory, EEPROM or SPIFFS for ESP8266
2. EEPROM and SPIFFS for ESP32.

It is tested and working with 
1. [`ESP8266 Core 2.6.2 or newer`](https://github.com/esp8266/Arduino)
2. [`ESP32 Core 1.0.4 or newer`](https://github.com/espressif/arduino-esp32)

### Quick Start

#### Use Arduino Library Manager

The easiest way is to use `Arduino Library Manager`. Search for `ESP_DoubleResetDetector`, then select / install the latest version.

#### Manual Install

The suggested way to install manually is to:

1. Navigate to [ESP_DoubleResetDetector](https://github.com/khoih-prog/ESP_DoubleResetDetector) page.
2. Download the latest release `ESP_DoubleResetDetector-master.zip`.
3. Extract the zip file to `ESP_DoubleResetDetector-master` directory 
4. Copy whole `ESP_DoubleResetDetector-master` folder to Arduino libraries' directory such as `~/Arduino/libraries`.

### Releases
#### New in v1.0.1

1. Add EEPROM and SPIFFS support, besides RTC memory, for ESP8266
2. Add SPIFFS support, besides EEPROM, for ESP32

#### PURPOSE:

Detects a double reset so that an alternative start-up mode can be used. One example use is to allow re-configuration of a device's wifi credentials.

#### Usage

How to use

```cpp
// These defines must be put before #include <ESP_DoubleResetDetector.h>
// to select where to store DoubleResetDetector's variable.
// For ESP32, You must select one to be true (EEPROM or SPIFFS)
// For ESP8266, You must select one to be true (RTC, EEPROM or SPIFFS)
// Otherwise, library will use default EEPROM storage
#define ESP_DRD_USE_EEPROM      false
#define ESP_DRD_USE_SPIFFS      true    //false

#ifdef ESP8266
  #define ESP8266_DRD_USE_RTC     false   //true
#endif

#define DOUBLERESETDETECTOR_DEBUG       true  //false

#include <ESP_DoubleResetDetector.h>      //https://github.com/khoih-prog/ESP_DoubleResetDetector

// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

DoubleResetDetector* drd;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("\Starting");
  
  drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);

  if (drd->detectDoubleReset()) 
  {
    Serial.println("Double Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
  } 
  else 
  {
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
  drd->loop();
}
```
### TO DO

1. Search for bug and improvement.
2. Similar features for Arduino (UNO, Mega, etc...)

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

### Copyright

Copyright 2019- Khoi Hoang
