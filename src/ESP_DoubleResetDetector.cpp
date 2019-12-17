/****************************************************************************************************************************
 * ESP_DoubleResetDetector.cpp
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

#include "ESP_DoubleResetDetector.h"

  #ifdef ESP32
    #include <EEPROM.h>
    static uint32_t DOUBLERESETDETECTOR_FLAG;
    
    #define  FLAG_DATA_SIZE     4

    #ifndef EEPROM_SIZE
      #define EEPROM_SIZE     512
    #endif  

    #ifndef EEPROM_START
      #define EEPROM_START    256
    #endif      
    
  #endif

#define DOUBLERESETDETECTOR_DEBUG       false

// Flag which will be stored in RTC memory.
// A uint32_t is used so that two different magic numbers can be used, 
// without accidentally overwriting memory used for another purpose.
uint32_t doubleResetDetectorFlag;

DoubleResetDetector::DoubleResetDetector(int timeout, int address) 
{
  #ifdef ESP32
    #if (DOUBLERESETDETECTOR_DEBUG)
      Serial.println("EEPROM size = " + String(EEPROM_SIZE) + ", start = " + String(EEPROM_START));
    #endif
    
    EEPROM.begin(EEPROM_SIZE);
  #endif
  
	this->timeout = timeout * 1000;
	this->address = address;
	doubleResetDetected = false;
	waitingForDoubleReset = false;
}

bool DoubleResetDetector::detectDoubleReset() 
{
	doubleResetDetected = detectRecentlyResetFlag();
	
	if (doubleResetDetected) 
	{
	  #if (DOUBLERESETDETECTOR_DEBUG)
	    Serial.println("doubleResetDetected");
	  #endif
		
		clearRecentlyResetFlag();
	} 
	else 
	{
	  #if (DOUBLERESETDETECTOR_DEBUG)
	    Serial.println("No doubleResetDetected");
	  #endif
		
		setRecentlyResetFlag();
		waitingForDoubleReset = true;
	}
	return doubleResetDetected;
}

void DoubleResetDetector::loop() 
{
	if (waitingForDoubleReset && millis() > timeout)
	{
	  #if (DOUBLERESETDETECTOR_DEBUG)
	    Serial.println("Stop doubleResetDetecting");
	  #endif
	  
	  stop();
	}
}

void DoubleResetDetector::stop() 
{
	clearRecentlyResetFlag();
	waitingForDoubleReset = false;
}

bool DoubleResetDetector::detectRecentlyResetFlag() 
{
	//doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG_CLEAR;
	
	#ifdef ESP8266
	  ESP.rtcUserMemoryRead(address, &doubleResetDetectorFlag, sizeof(doubleResetDetectorFlag));
	#else
	  EEPROM.get(EEPROM_START, DOUBLERESETDETECTOR_FLAG);
	  doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG;
	  
	  #if (DOUBLERESETDETECTOR_DEBUG)
	    Serial.println("EEPROM Flag read = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
	  #endif
	#endif
	
	doubleResetDetected = (doubleResetDetectorFlag == DOUBLERESETDETECTOR_FLAG_SET);
	return doubleResetDetected;
}

void DoubleResetDetector::setRecentlyResetFlag() {
	doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG_SET;
	
	#ifdef ESP8266
	  ESP.rtcUserMemoryWrite(address, &doubleResetDetectorFlag, sizeof(doubleResetDetectorFlag));
	#else
	  DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_FLAG_SET;
	  EEPROM.put(EEPROM_START, DOUBLERESETDETECTOR_FLAG);
	  EEPROM.commit();
	  	  
	  #if (DOUBLERESETDETECTOR_DEBUG)
	    delay(1000);
	    EEPROM.get(EEPROM_START, DOUBLERESETDETECTOR_FLAG);
	    Serial.println("SetFlag write = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
	  #endif
	#endif
}

void DoubleResetDetector::clearRecentlyResetFlag() {
	doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG_CLEAR;
	
	#ifdef ESP8266
	  ESP.rtcUserMemoryWrite(address, &doubleResetDetectorFlag, sizeof(doubleResetDetectorFlag));
	#else
	  DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_FLAG_CLEAR;
	  EEPROM.put(EEPROM_START, DOUBLERESETDETECTOR_FLAG);
	  EEPROM.commit();
	  
	  #if (DOUBLERESETDETECTOR_DEBUG)
	    delay(1000);
	    EEPROM.get(EEPROM_START, DOUBLERESETDETECTOR_FLAG);
	    Serial.println("ClearFlag write = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
	  #endif
	#endif
}
