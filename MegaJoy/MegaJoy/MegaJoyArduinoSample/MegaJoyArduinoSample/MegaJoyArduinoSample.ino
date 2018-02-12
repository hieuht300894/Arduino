
#include "MegaJoy.h"

void setup(){
  setupPins();
  setupMegaJoy();
}

void loop(){
  // Always be getting fresh data
  megaJoyControllerData_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins
  for (int i = 2; i <= 54; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

megaJoyControllerData_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  megaJoyControllerData_t controllerData = getBlankDataForMegaController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  for (int i = 2; i < 54; i++){
    controllerData.buttonArray[(i - 2) / 8] |= (!digitalRead(i)) << ((i - 2) % 8);
  }
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use 
  controllerData.analogAxisArray[0] = analogRead(A0);
  controllerData.analogAxisArray[1] = analogRead(A1); 
  controllerData.analogAxisArray[2] = 0; 
  controllerData.analogAxisArray[3] = 0; 
  controllerData.analogAxisArray[4] = 0; 
  controllerData.analogAxisArray[5] = 0; 
  controllerData.analogAxisArray[6] = 0; 
  controllerData.analogAxisArray[7] = 0; 
  controllerData.analogAxisArray[8] = 0; 
  controllerData.analogAxisArray[9] = 0; 
  controllerData.analogAxisArray[10] = 0; 
  controllerData.analogAxisArray[11] = 0; 
  
  // And return the data!
  return controllerData;
}
