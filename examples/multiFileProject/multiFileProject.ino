/****************************************************************************************************************************
  multiFileProject.ino
  
  For Nano_33_BLE or Nano_33_BLE_Sense boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_MBED_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
  #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define nRF52_MBED_PWM_VERSION_MIN_TARGET      "nRF52_MBED_PWM v1.0.1"
#define nRF52_MBED_PWM_VERSION_MIN             1000001

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "nRF52_MBED_PWM.h"

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStart multiFileProject");
  Serial.println(nRF52_MBED_PWM_VERSION);

#if defined(nRF52_MBED_PWM_VERSION_MIN)
  if (nRF52_MBED_PWM_VERSION_INT < nRF52_MBED_PWM_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(nRF52_MBED_PWM_VERSION_MIN_TARGET);
  }
#endif
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
