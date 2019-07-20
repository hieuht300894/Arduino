// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

#include <Joystick.h>

#define KEYS_TOTAL 16
#define RETRY_INTERVAL 50

/* Columns */
const byte C1 = 9;
const byte C2 = 8;
const byte C3 = 7;
const byte C4 = 6;

/* Rows */
const byte R1 = 5;
const byte R2 = 4;
const byte R3 = 3;
const byte R4 = 2;

unsigned long retry = 0;

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
  Joystick.setXAxis(0);
  Joystick.setYAxis(0);
  Joystick.setZAxis(0);
  Joystick.setXAxisRotation(180);
  Joystick.setYAxisRotation(180);
  Joystick.setZAxisRotation(180);
  Joystick.setThrottle(127);
  Joystick.setRudder(127);
}

void loop() {
  if ((unsigned long)(millis() - retry) > RETRY_INTERVAL)
  {  
    handleButtonStatus();
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
