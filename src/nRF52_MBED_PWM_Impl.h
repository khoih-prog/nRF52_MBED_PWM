/****************************************************************************************************************************
  nRF52_MBED_PWM_Impl.h
  For Nano_33_BLE or Nano_33_BLE_Sense boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_MBED_PWM
  Licensed under MIT license

  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      09/02/2022 Initial coding for Nano_33_BLE /  Nano_33_BLE_Sense using ArduinoCore-mbed mbed_nano core
*****************************************************************************************************************************/

#ifndef nRF52_MBED_PWM_IMPL_H
#define nRF52_MBED_PWM_IMPL_H

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_       1
#endif

#include "Arduino.h"
#include "nRF52_MBED_PWM.h"

#include "PWM_Generic_Debug.h"

// All the digital pins on Arduino Nano 33 BLE sense are PWM-enabled pins which are numbered from D0 to D13
// https://www.etechnophiles.com/arduino-nano-33-ble-sense-pinout-introduction-specifications/
bool isValidPWMPin(const pin_size_t& pin)
{
  if ( (pin == D0) || (pin == D1) || (pin == D2) || (pin == D3)  || (pin == D4)  || (pin == D5)  || (pin == D6) || \
       (pin == D7) || (pin == D8) || (pin == D9) || (pin == D10) || (pin == D11) || (pin == D12) || (pin == D13) )
  {
    return true;
  }
  
  PWM_LOGERROR1("Not PWM pin = ", pin);
  
  return false;
}

bool isValidPWMDutyCycle(const pin_size_t& pin, const float& dutyCycle)
{
  if ( (dutyCycle < 0.0f) || (dutyCycle > 100.0f) )
  {
    PWM_LOGERROR3("Bad dutyCycle = ", dutyCycle, ", pin = ", pin);
    
    return false;
  }

  return true;
}

// Check if freq > 0
bool isValidPWMFreq(const pin_size_t& pin, const float& frequency)
{
  if ( frequency <= 0.0f )
  {
    PWM_LOGERROR3("Bad Freq = ", frequency, ", pin = ", pin);

    return false;
  }
  
  return true;
}

bool isValidPWMSettings(const pin_size_t& pin, const float& frequency, const float& dutyCycle)
{
  if ( !isValidPWMPin(pin) || !isValidPWMFreq(pin, frequency) || !isValidPWMDutyCycle(pin, dutyCycle) )
  { 
    return false;
  } 
  
  return true;
}

// dutyCycle from 0.0f to 100.0f
mbed::PwmOut* setPWM(mbed::PwmOut* &pwm, const pin_size_t& pin, const float& frequency, const float& dutyCycle)
{
  PWM_LOGDEBUG7("Freq = ", frequency, ", \tDutyCycle = ", dutyCycle, ", \tDutyCycle % = ", dutyCycle / 100, ", \tPin = ", pin);
    
  if ( !isValidPWMSettings(pin, frequency, dutyCycle) )
  {   
    return NULL;
  }

  float percent = dutyCycle / 100.0f;
  
  if (digitalPinToPwm(pin) == NULL)
  {
    PWM_LOGDEBUG("New pwm");
    
    pwm = new mbed::PwmOut(digitalPinToPinName(pin));
    
    digitalPinToPwm(pin) = pwm;

    pwm->period_us( 1000000.0f/frequency );  

    pwm->write(percent);
  }
  else if (pwm && (digitalPinToPwm(pin) == pwm) )
  {
    PWM_LOGDEBUG("Use existing pwm");
    
    pwm->period_us( 1000000.0f/frequency );  

    pwm->write(percent);
  }
  
  return pwm;
}

mbed::PwmOut* stopPWM(mbed::PwmOut* &pwm, const pin_size_t& pin)
{
  return setPWM(pwm, pin, 1000.0f, 0.0f);
}

#endif    // nRF52_MBED_PWM_IMPL_H


