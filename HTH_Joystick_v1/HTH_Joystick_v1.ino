/*HTH 12-02-2018*/

#include "MegaJoy.h"

/*IC1*/
int IC1_pin_In_Mux = 3; //~Z
int IC1_pin_Out_S0 = 8; //SO
int IC1_pin_Out_S1 = 9; //S1
int IC1_pin_Out_S2 = 10; //S2

/*IC2*/
int IC2_pin_In_Mux = 2; //~Z
int IC2_pin_Out_S0 = 5; //SO
int IC2_pin_Out_S1 = 6; //S1
int IC2_pin_Out_S2 = 7; //S2

void setup() {
  setupPins();
  setupMegaJoy();
}

void loop() {
  // Always be getting fresh data
  megaJoyControllerData_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void) {
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the
  // two serial line pins
  for (int i = 22; i < 54; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }

  pinMode(IC1_pin_In_Mux, INPUT);
  pinMode(IC1_pin_Out_S0, OUTPUT);
  pinMode(IC1_pin_Out_S1, OUTPUT);
  pinMode(IC1_pin_Out_S2, OUTPUT);

  pinMode(IC2_pin_In_Mux, INPUT);
  pinMode(IC2_pin_Out_S0, OUTPUT);
  pinMode(IC2_pin_Out_S1, OUTPUT);
  pinMode(IC2_pin_Out_S2, OUTPUT);
}

megaJoyControllerData_t getControllerData(void) {

  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  megaJoyControllerData_t controllerData = getBlankDataForMegaController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins

  int pin_Start = 22;
  int pin_Current=22;
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(IC1_pin_In_Mux, LOW);
    digitalWrite(IC1_pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(IC1_pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(IC1_pin_Out_S2, HIGH && (i & B00000100));
    controllerData.buttonArray[(pin_Current - pin_Start) / 8] |= (digitalRead(IC1_pin_In_Mux)) << ((pin_Current - pin_Start) % 8);
    pin_Current++;
  }
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(IC2_pin_In_Mux, LOW);
    digitalWrite(IC2_pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(IC2_pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(IC2_pin_Out_S2, HIGH && (i & B00000100));
    controllerData.buttonArray[(pin_Current - pin_Start) / 8] |= (digitalRead(IC2_pin_In_Mux)) << ((pin_Current - pin_Start) % 8);
    pin_Current++;
  }

  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use
  // Use index 2,3,4,5
  controllerData.analogAxisArray[0] = 0;
  controllerData.analogAxisArray[1] = 0;
  controllerData.analogAxisArray[2] = 512;  // Z Axis
  controllerData.analogAxisArray[3] = analogRead(A1);  // X Rotation
  controllerData.analogAxisArray[4] = analogRead(A2);// Y Rotation
  controllerData.analogAxisArray[5] = analogRead(A3);// Z Rotation
  controllerData.analogAxisArray[6] = 0;
  controllerData.analogAxisArray[7] = 0;
  controllerData.analogAxisArray[8] = 0;
  controllerData.analogAxisArray[9] = 0;
  controllerData.analogAxisArray[10] = 0;
  controllerData.analogAxisArray[11] = 0;

  // And return the data!
  return controllerData;
}
