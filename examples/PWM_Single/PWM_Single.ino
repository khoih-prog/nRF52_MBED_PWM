/****************************************************************************************************************************
  PWM_Single.ino
  For Nano_33_BLE or Nano_33_BLE_Sense boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_MBED_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
  #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define _PWM_LOGLEVEL_       1

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "nRF52_MBED_PWM.h"

#define LED_ON        LOW
#define LED_OFF       HIGH

// All the digital pins on Arduino Nano 33 BLE sense are PWM-enabled pins which are numbered from D0 to D13
uint32_t myPin  = D2;

float dutyCycle = 50.0f;

float freq      = 5000.0f;

float curDutyCycle  = dutyCycle;

float curFreq       = freq;

mbed::PwmOut* pwm   = NULL;

void startPWM()
{
  digitalWrite(LEDG, LED_ON);
  digitalWrite(LEDB, LED_OFF);
  digitalWrite(LEDR, LED_OFF);

  PWM_LOGERROR7("Freq = ", freq, ", DutyCycle % = ", dutyCycle, ", DutyCycle = ", dutyCycle / 100, ", Pin = ", myPin);
  setPWM(pwm, myPin, freq, dutyCycle);
}

void restorePWM()
{
  digitalWrite(LEDG, LED_ON);
  digitalWrite(LEDB, LED_OFF);
  digitalWrite(LEDR, LED_OFF);
  
  curFreq      = freq;
  curDutyCycle = dutyCycle;
  
  // setPWM(mbed::PwmOut* &pwm, pin_size_t pin, float frequency, float dutyCycle)
  setPWM(pwm, myPin, freq, dutyCycle);
}

void changePWM()
{
  digitalWrite(LEDG, LED_OFF);
  digitalWrite(LEDB, LED_ON);
  digitalWrite(LEDR, LED_OFF);
  
  curFreq      = freq * 2;
  curDutyCycle = dutyCycle / 2;
  
  // setPWM(mbed::PwmOut* &pwm, pin_size_t pin, float frequency, float dutyCycle)
  setPWM(pwm, myPin, curFreq, curDutyCycle);
}

void stopMyPWM()
{
  digitalWrite(LEDG, LED_OFF);
  digitalWrite(LEDB, LED_OFF);
  digitalWrite(LEDR, LED_ON);
  
  curFreq      = 1000.0f;
  curDutyCycle = 0.0f;
  
  //stopPWM(mbed::PwmOut* &pwm, pin_size_t pin)
  stopPWM(pwm, myPin);
}

void printLine()
{
  Serial.println(F("\n============================================"));
}

void printPulseWidth()
{
  static uint32_t num = 0;

  if (num++ % 50 == 0)
  {
    printLine();
    
    Serial.print(F("PW (us)\t\tDutyCycle\tPeriod (uS)"));

    printLine();
  }
 
  if (num > 1)
  {
    if (pwm)
    {
      Serial.print(getPulseWidth_uS(pwm)); Serial.print(F("\t\t"));
      Serial.print(getDutyCycle(pwm)); Serial.print(F("\t\t"));
      Serial.print(getPeriod_uS(pwm));
    }

    Serial.println();
  }
}

#define PRINT_INTERVAL      10000L
#define CHANGE_INTERVAL     20000L

void check_status()
{
  static unsigned long checkstatus_timeout  = 0;
  static unsigned long changePWM_timeout    = 0;

  static bool PWM_orig  = true;
  static uint32_t count = 0;

  // Print every PRINT_INTERVAL (10) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    printPulseWidth();
    checkstatus_timeout = millis() + PRINT_INTERVAL;
  }

  if ( (millis() > changePWM_timeout) && (millis() > CHANGE_INTERVAL) )
  {
    
    if (PWM_orig)
    {
      if (count++ %2 == 0)
      {
        Serial.println("Stop PWM");
        stopMyPWM();
      }
      else
      {
        Serial.println("Change PWM");
        
        changePWM();

        PWM_orig = !PWM_orig;
      }
    }
    else
    {
      Serial.println("Restore PWM");
      
      restorePWM();

      PWM_orig = !PWM_orig;
    }
      
    changePWM_timeout = millis() + CHANGE_INTERVAL;
  }
}

void setup()
{
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDR, OUTPUT);

  digitalWrite(LEDG, LED_OFF);
  digitalWrite(LEDB, LED_OFF);
  digitalWrite(LEDR, LED_OFF);

  pinMode(myPin, OUTPUT);
  digitalWrite(myPin, LOW);

  Serial.begin(115200);
  while (!Serial);

  delay(100);

  Serial.print(F("\nStarting PWM_Single on ")); Serial.println(BOARD_NAME);
  Serial.println(nRF52_MBED_PWM_VERSION);

  startPWM();
}

void loop()
{
  check_status();
}
