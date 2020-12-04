## ESP_DoubleResetDetector

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP_DoubleResetDetector.svg)](https://github.com/khoih-prog/ESP_DoubleResetDetector/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP_DoubleResetDetector/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP_DoubleResetDetector.svg)](http://github.com/khoih-prog/ESP_DoubleResetDetector/issues)

---
---

### Releases v1.1.0

1. Add support to LittleFS for ESP32 using [LITTLEFS](https://github.com/lorol/LITTLEFS) Library

### Releases v1.0.3

1. Update to use the new LittleFS for ESP8266 core 2.7.1+
2. Update [minimal example](examples/minimal)

### Releases v1.0.2

1. Fix bug by left-over cpp file.
2. Fix bug in example.
3. Enhance README.md

This library is based on, modified, bug-fixed and improved from [`DataCute`](https://github.com/datacute/DoubleResetDetector) to add support for ESP32.
 
Using this library to detect a double reset, using

1. RTC Memory, EEPROM, LittleFS or SPIFFS for ESP8266
2. EEPROM and SPIFFS for ESP32.

## Prerequisites

1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`ESP32 Core 1.0.4+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards
3. [`ESP8266 Core 2.7.4+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. SPIFFS is deprecated from ESP8266 core 2.7.1+. 

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `ESP_DoubleResetDetector`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector) for more detailed instructions.

### Manual Install

1. Navigate to [ESP_DoubleResetDetector](https://github.com/khoih-prog/ESP_DoubleResetDetector) page.
2. Download the latest release `ESP_DoubleResetDetector-master.zip`.
3. Extract the zip file to `ESP_DoubleResetDetector-master` directory 
4. Copy the whole `ESP_DoubleResetDetector-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ESP_DoubleResetDetector** library](https://platformio.org/lib/show/6935/ESP_DoubleResetDetector) by using [Library Manager](https://platformio.org/lib/show/6935/ESP_DoubleResetDetector/installation). Search for **ESP_DoubleResetDetector** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

#### PURPOSE:

Detects a double reset so that an alternative start-up mode can be used. One example use is to allow re-configuration of a device's wifi credentials.

---

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

### Examples

1. [ConfigOnDoubleReset](examples/ConfigOnDoubleReset)
2. [minimal](examples/minimal)

### Examples from other libraries

#### 1.[ESP_WiFiManager Library](https://github.com/khoih-prog/ESP_WiFiManager)

1. [ConfigOnDoubleReset](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ConfigOnDoubleReset)
2. [ConfigOnDRD_FS_MQTT_Ptr](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ConfigOnDRD_FS_MQTT_Ptr)
3. [ESP32_FSWebServer_DRD](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ESP32_FSWebServer_DRD)
4. [ESP_FSWebServer_DRD](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ESP_FSWebServer_DRD)


#### 2. [ESPAsync_WiFiManager Library](https://github.com/khoih-prog/ESPAsync_WiFiManager)

1. [Async_ConfigOnDRD_FS_MQTT_Ptr](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ConfigOnDRD_FS_MQTT_Ptr)
2. [Async_ConfigOnDRD_FS_MQTT_Ptr](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ConfigOnDRD_FS_MQTT_Ptr)
3. [Async_ESP32_FSWebServer_DRD](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ESP32_FSWebServer_DRD)
4. [Async_ESP_FSWebServer_DRD](https://github.com/khoih-prog/ESPAsync_WiFiManager/tree/master/examples/Async_ESP_FSWebServer_DRD)

and there are many more.

---
---

### Debug Termimal Output Samples

1. This is terminal debug output when running [ESP32_FSWebServer_DRD](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ESP32_FSWebServer_DRD) on  ***ESP32 ESP32_DEV.***. Config Portal was requested by DRD to input and save Credentials. The boards then connected to WiFi AP **HueNet1** using new Static IP successfully. WiFi AP **HueNet1** is then lost, and board **autoreconnects** itself to backup WiFi AP **HueNet2**.

```cpp
Starting ESP32_FSWebServer_DRD with DoubleResetDetect using SPIFFS on ESP32_DEV
ESP_WiFiManager Version v1.3.0
ESP_DoubleResetDetector Version v1.1.0
FS File: /ConfigSW.json, size: 150B
FS File: /CanadaFlag_1.png, size: 40.25KB
FS File: /CanadaFlag_2.png, size: 8.12KB
FS File: /CanadaFlag_3.jpg, size: 10.89KB
FS File: /edit.htm.gz, size: 4.02KB
FS File: /favicon.ico, size: 1.12KB
FS File: /graphs.js.gz, size: 1.92KB
FS File: /index.htm, size: 3.63KB
FS File: /drd.dat, size: 4B
FS File: /wifi_cred.dat, size: 192B

[WM] RFC925 Hostname = ESP32-FSWebServerDRD
[WM] setAPStaticIPConfig
[WM] setSTAStaticIPConfig for USE_CONFIGURABLE_DNS
[WM] Set CORS Header to :  Your Access-Control-Allow-Origin
Stored: SSID = HueNet2, Pass = 12345678
[WM] * Add SSID =  HueNet2 , PW =  12345678
Got stored Credentials. Timeout 120s for Config Portal
SPIFFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[WM] LoadWiFiCfgFile 
[WM] OK
[WM] * Add SSID =  HueNet1 , PW =  12345678
[WM] * Add SSID =  HueNet2 , PW =  12345678
ConnectMultiWiFi in setup
[WM] ConnectMultiWiFi with :
[WM] * Flash-stored Router_SSID =  HueNet2 , Router_Pass =  12345678
[WM] * Additional SSID =  HueNet1 , PW =  12345678
[WM] * Additional SSID =  HueNet2 , PW =  12345678
[WM] Connecting MultiWifi...
[WM] WiFi connected after time:  1
[WM] SSID: HueNet1 ,RSSI= -27
[WM] Channel: 2 ,IP address: 192.168.2.232
After waiting 3.16 secs more in setup(), connection result is connected. Local IP: 192.168.2.232
HTTP server started @ 192.168.2.232
Open http://esp32-fs-browser.local/edit to see the file browser
[WM] freeing allocated params!
Stop doubleResetDetecting
Saving config file...
Saving config file OK

WiFi lost. Call connectMultiWiFi in loop
[WM] ConnectMultiWiFi with :
[WM] * Flash-stored Router_SSID =  HueNet2 , Router_Pass =  12345678
[WM] * Additional SSID =  HueNet1 , PW =  12345678
[WM] * Additional SSID =  HueNet2 , PW =  12345678
[WM] Connecting MultiWifi...
[WM] WiFi connected after time:  3
[WM] SSID: HueNet2 ,RSSI= -59
[WM] Channel: 4 ,IP address: 192.168.2.232
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
```

---

1. This is terminal debug output when running [ConfigOnDoubleReset](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ConfigOnDoubleReset) on  ***ESP32 ESP32_DEV.***. Config Portal was requested by DRD to input and save Credentials.


```

Starting ConfigOnDoubleReset with DoubleResetDetect using LittleFS on ESP32_DEV
ESP_WiFiManager Version v1.3.0
ESP_DoubleResetDetector Version v1.1.0
[WM] RFC925 Hostname = ConfigOnDoubleReset
[WM] Set CORS Header to :  Your Access-Control-Allow-Origin
Stored: SSID = HueNet1, Pass = 12345678
[WM] * Add SSID =  HueNet1 , PW =  87654321
Got stored Credentials. Timeout 120s for Config Portal
LittleFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[WM] LoadWiFiCfgFile 
[WM] OK
[WM] * Add SSID =  HueNet1 , PW =  jenniqqs
[WM] * Add SSID =  HueNet2 , PW =  jenniqqs
ConnectMultiWiFi in setup
[WM] ConnectMultiWiFi with :
[WM] * Flash-stored Router_SSID =  HueNet1 , Router_Pass =  jenniqqs
[WM] * Additional SSID =  HueNet1 , PW =  12345678
[WM] * Additional SSID =  HueNet2 , PW =  87654321
[WM] Connecting MultiWifi...
[WM] WiFi connected after time:  1
[WM] SSID: HueNet1 ,RSSI= -32
[WM] Channel: 2 ,IP address: 192.168.2.101
After waiting 4.43 secs more in setup(), connection result is connected. Local IP: 192.168.2.101
[WM] freeing allocated params!
HStop doubleResetDetecting
Saving config file...
Saving config file OK
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0018,len:4
load:0x3fff001c,len:1216
ho 0 tail 12 room 4
load:0x40078000,len:9720
ho 0 tail 12 room 4
load:0x40080400,len:6352
entry 0x400806b8

Starting ConfigOnDoubleReset with DoubleResetDetect using LittleFS on ESP32_DEV
ESP_WiFiManager Version v1.3.0
ESP_DoubleResetDetector Version v1.1.0
[WM] RFC925 Hostname = ConfigOnDoubleReset
[WM] Set CORS Header to :  Your Access-Control-Allow-Origin
Stored: SSID = HueNet1, Pass = jenniqqs
[WM] * Add SSID =  HueNet1 , PW =  jenniqqs
Got stored Credentials. Timeout 120s for Config Portal
LittleFS Flag read = 0xd0d01234
doubleResetDetected
Saving config file...
Saving config file OK
Open Config Portal without Timeout: Double Reset Detected
Starting configuration portal.
[WM] WiFi.waitForConnectResult Done
[WM] SET AP
[WM] Configuring AP SSID = ESP_9ABF498
[WM] AP PWD = your_password
[WM] AP Channel = 3
[WM] AP IP address = 192.168.4.1
[WM] HTTP server started
[WM] ESP_WiFiManager::startConfigPortal : Enter loop

```

---
---

### Releases

### Releases v1.1.0

1. Add support to LittleFS for ESP32 using [LITTLEFS](https://github.com/lorol/LITTLEFS) Library

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
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the `ESP32 / ESP8266` core for Arduino.

Sometimes, the library will only work if you update the `ESP32 / ESP8266` core to the latest version because I am using some newly added function.

---

### Issues ###

Submit issues to: [ESP_DoubleResetDetector issues](https://github.com/khoih-prog/ESP_DoubleResetDetector/issues)

---
---

### TO DO

1. Search for bug and improvement.


### DONE

1. For ESP32 and ESP8266 (EEPROM, SPIFFS and LittleFS).
2. Similar features for Arduino (UNO, Mega, SAM DUE, SAMD21/SAMD51, nRF52, STM32, Teensy, etc.). Look at [**DoubleResetDetector_Generic**](https://github.com/khoih-prog/DoubleResetDetector_Generic)


---
---

### Contributions and thanks

1. Thanks to [zobix](https://github.com/zobix) for report the bug in [Isssue 2](https://github.com/khoih-prog/ESP_DoubleResetDetector/issues/2)

<table>
  <tr>
    <td align="center"><a href="https://github.com/zobix"><img src="https://github.com/zobix.png" width="100px;" alt="zobix"/><br /><sub><b>Zobix</b></sub></a><br /></td>
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

### License and credits ###

- The library is licensed under [MIT](https://github.com/khoih-prog/ESP_DoubleResetDetector/blob/master/LICENSE)

---

### Copyright

Copyright 2019- Khoi Hoang
