// Program used to test the USB Joystick object on the 
// Arduino Leonardo or Arduino Micro.
//
// Matthew Heironimus
// 2015-03-28 - Original Version
// 2015-11-18 - Updated to use the new Joystick library 
//              written for Arduino IDE Version 1.6.6 and
//              above.
// 2016-05-13   Updated to use new dynamic Joystick library
//              that can be customized.
//------------------------------------------------------------

#include "Joystick.h"
#define RETRY_INTERVAL 10

// Create Joystick
Joystick_ Joystick;

/* Columns */
const byte C1 = 10;
const byte C2 = 16;
const byte C3 = 14;
const byte C4 = 15;

/* Rows */
const byte R1 = 9;
const byte R2 = 8;
const byte R3 = 7;
const byte R4 = 6;

/* Volant Encoder*/
const byte pin_interrupt = 1;
const byte pin_A = 2;
const byte pin_B = 3;

unsigned long retry = 0;
int pulse = 512;
int pulseMax = 512;
int pulseMin = 512;

void setup() {
  // Initialize Joystick Library
  Joystick.begin();
  // Initialze button
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  pinMode(R3, INPUT);
  pinMode(R4, INPUT);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  attachInterrupt(pin_interrupt, rotate, FALLING);
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);

  Joystick.setThrottle(pulse);
}

void loop() {
  if ((unsigned long)(millis() - retry) > RETRY_INTERVAL)
  {
    handleButtonStatus();
    handleVolantStatus();
    retry = millis();
  }
}

void handleButtonStatus() {
  byte index = 0;
  digitalWrite(C1, HIGH);
  digitalWrite(C2, LOW);
  digitalWrite(C3, LOW);
  digitalWrite(C4, LOW);
  Joystick.setButton(index++, digitalRead(R1));
  Joystick.setButton(index++, digitalRead(R2));
  Joystick.setButton(index++, digitalRead(R3));
  Joystick.setButton(index++, digitalRead(R4));
  digitalWrite(C1, LOW);
  digitalWrite(C2, HIGH);
  digitalWrite(C3, LOW);
  digitalWrite(C4, LOW);
  Joystick.setButton(index++, digitalRead(R1));
  Joystick.setButton(index++, digitalRead(R2));
  Joystick.setButton(index++, digitalRead(R3));
  Joystick.setButton(index++, digitalRead(R4));
  digitalWrite(C1, LOW);
  digitalWrite(C2, LOW);
  digitalWrite(C3, HIGH);
  digitalWrite(C4, LOW);
  Joystick.setButton(index++, digitalRead(R1));
  Joystick.setButton(index++, digitalRead(R2));
  Joystick.setButton(index++, digitalRead(R3));
  Joystick.setButton(index++, digitalRead(R4));
  digitalWrite(C1, LOW);
  digitalWrite(C2, LOW);
  digitalWrite(C3, LOW);
  digitalWrite(C4, HIGH);
  Joystick.setButton(index++, digitalRead(R1));
  Joystick.setButton(index++, digitalRead(R2));
  Joystick.setButton(index++, digitalRead(R3));
  Joystick.setButton(index++, digitalRead(R4));
}

void handleVolantStatus() {
  Joystick.setThrottle(map(pulse, pulseMin, pulseMax, 0 , 1023));
}

void rotate() {
  if (digitalRead(pin_B) == LOW) {
    pulse++;
  } else {
    pulse--;
  }

  if (pulse > pulseMax) {
    pulseMax = pulse;
  } else if (pulse < pulseMin) {
    pulseMin = pulse;
  }
}
