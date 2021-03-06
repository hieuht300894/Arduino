#include <Joystick.h>

#define RETRY_INTERVAL 10

// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

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
int pulse = 0;
int pulseMax = 0;
int pulseMin = 0;

Joystick_ Joystick;

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

void handleVolantStatus() {
  Joystick.setRudder(map(pulse, pulseMin, pulseMax, 0 , 255));
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
