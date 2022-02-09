/****************************************************************************************************************************
  nRF52_MBED_PWM.hpp
  For Nano_33_BLE or Nano_33_BLE_Sense boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_MBED_PWM
  Licensed under MIT license

  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      09/02/2022 Initial coding for Nano_33_BLE /  Nano_33_BLE_Sense using ArduinoCore-mbed mbed_nano core
*****************************************************************************************************************************/

#pragma once

#ifndef nRF52_MBED_PWM_HPP
#define nRF52_MBED_PWM_HPP

#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
  #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#ifndef nRF52_MBED_PWM_VERSION
  #define nRF52_MBED_PWM_VERSION             "nRF52_MBED_PWM v1.0.0"
  
  #define nRF52_MBED_PWM_VERSION_MAJOR       1
  #define nRF52_MBED_PWM_VERSION_MINOR       0
  #define nRF52_MBED_PWM_VERSION_PATCH       0

  #define nRF52_MBED_PWM_VERSION_INT         1000000
#endif


///////////////////////////////////////////

#include "Arduino.h"
#include "pinDefinitions.h"
#include "PwmOut.h"

///////////////////////////////////////////
  
  
///////////////////////////////////////////

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_       1
#endif

#include "PWM_Generic_Debug.h"

///////////////////////////////////////////

bool isValidPWMPin(const pin_size_t& pin);

bool isValidPWMFreq(const pin_size_t& pin, const float& frequency);

bool isValidPWMDutyCycle(const pin_size_t& pin, const float& dutyCycle);

bool isUsingHRTIM(const pin_size_t& pin);

bool isValidPWMSettings(const pin_size_t& pin, const float& frequency, const float& dutyCycle);

mbed::PwmOut* setPWM(mbed::PwmOut* &pwm, const pin_size_t& pin, const float& frequency, const float& dutyCycle);

mbed::PwmOut* stopPWM(mbed::PwmOut* &pwm, const pin_size_t& pin);

#endif    // nRF52_MBED_PWM_HPP

