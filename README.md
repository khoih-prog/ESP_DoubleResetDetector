## ESP_DoubleResetDetector

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP_DoubleResetDetector.svg)](https://github.com/khoih-prog/ESP_DoubleResetDetector/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP_DoubleResetDetector/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP_DoubleResetDetector.svg)](http://github.com/khoih-prog/ESP_DoubleResetDetector/issues)

---
---

### Releases v1.0.3

1. Update to use the new LittleFS for ESP8266 core 2.7.1+
2. Update [minimal example](examples/minimal)

### Releases v1.0.2

1. Fix bug by left-over cpp file.
2. Fix bug in example.
3. Enhance README.md

---

This library is based on, modified, bug-fixed and improved from [`Stephen Denne's DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) to add support for ESP32 and ESP8266 using EEPROM, LittleFS or SPIFFS besides RTC memory.
 
Using this library to detect a double reset, using:

1. RTC Memory, EEPROM, LittleFS or SPIFFS for ESP8266
2. EEPROM and SPIFFS for ESP32.

---
---

## Prerequisite

1. [`Arduino IDE 1.8.12+` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`ESP32 core 1.0.4+`](https://github.com/espressif/arduino-esp32/releases) for ESP32 (Use Arduino Board Manager)
3. [`ESP8266 core 2.7.3+`](https://github.com/esp8266/Arduino/releases) for ES82662 (Use Arduino Board Manager) to use LittleFS or SPIFFS. SPIFFS is deprecated from ESP8266 core 2.7.1.

---
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `ESP_DoubleResetDetector`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [ESP_DoubleResetDetector](https://github.com/khoih-prog/ESP_DoubleResetDetector) page.
2. Download the latest release `ESP_DoubleResetDetector-master.zip`.
3. Extract the zip file to `ESP_DoubleResetDetector-master` directory 
4. Copy whole `ESP_DoubleResetDetector-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:
1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **ESP_DoubleResetDetector** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for ESP_DoubleResetDetector in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---

#### PURPOSE:

**Detects a double reset so that an alternative start-up mode can be used**. One example use is to allow re-configuration of a device's wifi credentials.

#### HOWTO Usage

How to use

```cpp
// These defines must be put before #include <ESP_DoubleResetDetector.h>
// to select where to store DoubleResetDetector's variable.
// For ESP32, You must select one to be true (EEPROM or SPIFFS)
// For ESP8266, You must select one to be true (RTC, EEPROM, LITTLEFS or SPIFFS)
// Otherwise, library will use default EEPROM storage


#ifdef ESP8266
#define ESP8266_DRD_USE_RTC     false   //true
#define ESP_DRD_USE_LITTLEFS    true    //false
#endif

#define ESP_DRD_USE_EEPROM      false
#define ESP_DRD_USE_SPIFFS      true

#define DOUBLERESETDETECTOR_DEBUG       true  //false

#include <ESP_DoubleResetDetector.h>      //https://github.com/khoih-prog/ESP_DoubleResetDetector

// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

DoubleResetDetector* drd;

#ifdef ESP32

// For ESP32
#ifndef LED_BUILTIN
#define LED_BUILTIN       2         // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
#endif

#define LED_OFF     LOW
#define LED_ON      HIGH

#else

// For ESP8266
#define LED_ON      LOW
#define LED_OFF     HIGH

#endif

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("\nStarting minimal example for ESP_DoubleResetDetector");
  
  drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);

  if (drd->detectDoubleReset()) 
  {
    Serial.println("Double Reset Detected");
    digitalWrite(LED_BUILTIN, LED_ON);
  } 
  else 
  {
    Serial.println("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, LED_OFF);
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
---
---

### Examples: 

 1. [ConfigOnDoubleReset](examples/ConfigOnDoubleReset)
 2. [minimal](examples/minimal)

### Examples from other libraries

#### [ESP_WiFiManager Library](https://github.com/khoih-prog/ESP_WiFiManager)

 3. [ConfigOnDoubleReset](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ConfigOnDoubleReset)
 4. [ESP32_FSWebServer_DRD](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ESP32_FSWebServer_DRD)
 5. [ESP_FSWebServer_DRD](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ESP_FSWebServer_DRD)

#### [ESPAsync_WiFiManager Library](https://github.com/khoih-prog/ESPAsync_WiFiManager)

 6. [Async_ConfigOnDoubleReset](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ConfigOnDoubleReset)
 7. [Async_ConfigOnDRD_FS_MQTT_Ptr](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ConfigOnDRD_FS_MQTT_Ptr)
 8. [Async_ESP32_FSWebServer_DRD](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ESP32_FSWebServer_DRD)
 9. [Async_ESP_FSWebServer_DRD](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ESP_FSWebServer_DRD)

---

#### And many other libraries are depending on this DRD feature

  All examples of these following libraries are using DRD feature of this [ESP_DoubleResetDetector Library](https://github.com/khoih-prog/ESP_DoubleResetDetector)
  
  1. [Blynk_WM](https://github.com/khoih-prog/Blynk_WM), 
  2. [BlynkESP32_BT_WF](https://github.com/khoih-prog/BlynkESP32_BT_WF), 
  3. [Blynk_GSM_Manager](https://github.com/khoih-prog/Blynk_GSM_Manager), 
  4. [Blynk_Async_WM](https://github.com/khoih-prog/Blynk_Async_WM),
  5. [Blynk_Async_ESP32_BT_WF](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF), 
  6. [Blynk_Async_GSM_Manager](https://github.com/khoih-prog/Blynk_Async_GSM_Manager), 

  and many more.

---

### Releases

### Releases v1.0.3

1. Update to use the new LittleFS for ESP8266 core 2.7.1+
2. Update [minimal example](examples/minimal)

#### Releases v1.0.2

1. Fix bug by left-over cpp file.
2. Fix bug in example.
3. Enhance README.md

#### Releases v1.0.1

1. Add EEPROM and SPIFFS support, besides RTC memory, for ESP8266
2. Add SPIFFS support, besides EEPROM, for ESP32

---

### TO DO

1. Search for bug and improvement.
2. Similar features for Arduino (UNO, Mega, etc...)

---

### Issues

Submit issues to: [ESP_DoubleResetDetector issues](https://github.com/khoih-prog/ESP_DoubleResetDetector/issues)

---

### Contributions and thanks

1. Thanks to [Stephen Denne](https://github.com/datacute) for the [`DoubleResetDetector library`](https://github.com/datacute/DoubleResetDetector) this library is based upon.
2. Thanks to [zobix](https://github.com/zobix) for report the bug in [Isssue 2](https://github.com/khoih-prog/ESP_DoubleResetDetector/issues/2)

<table>
  <tr>
    <td align="center"><a href="https://github.com/datacute"><img src="https://github.com/datacute.png" width="100px;" alt="datacute"/><br /><sub><b>⭐️ Stephen Denne</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/zobix"><img src="https://github.com/zobix.png" width="100px;" alt="zobix"/><br /><sub><b>zobix</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing
If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/ESP_DoubleResetDetector/blob/master/LICENSE)

---

### Copyright

Copyright 2019- Khoi Hoang
