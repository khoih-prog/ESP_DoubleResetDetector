/****************************************************************************************************************************
 * ESP_DoubleResetDetector.h
 * For ESP8266 / ESP32 boards
 *
 * ESP_DoubleResetDetector is a library for the ESP8266/Arduino platform
 * to enable trigger configure mode by resetting ESP32 / ESP8266 twice.
 *
 * Forked from DataCute https://github.com/datacute/DoubleResetDetector
 * 
 * Built by Khoi Hoang https://github.com/khoih-prog/ESP_DoubleResetDetector
 * Licensed under MIT license
 * Version: 1.0.0
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      15/12/2019 Initial coding
 *****************************************************************************************************************************/

#ifndef ESP_DoubleResetDetector_H
#define ESP_DoubleResetDetector_H

#if defined(ARDUINO) && (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#define ESP_DOUBLERESETDETECTOR_VERSION "1.0.0"

#define DOUBLERESETDETECTOR_FLAG_SET    0xD0D01234
#define DOUBLERESETDETECTOR_FLAG_CLEAR  0xD0D04321

class DoubleResetDetector
{
public:
	DoubleResetDetector(int timeout, int address);
	bool detectDoubleReset();
	bool doubleResetDetected;
	void loop();
	void stop();
	
private:
	int timeout;
	int address;
	bool waitingForDoubleReset;
	bool detectRecentlyResetFlag();
	void clearRecentlyResetFlag();
	void setRecentlyResetFlag();
	uint32_t doubleResetDetectorFlag;
};
#endif // DoubleResetDetector_H
