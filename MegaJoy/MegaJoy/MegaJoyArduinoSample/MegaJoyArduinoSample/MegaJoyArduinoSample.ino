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
  for (int i = 22; i < 54; i++){
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
  for (int i = 22; i < 54; i++){
    controllerData.buttonArray[(i - 22) / 8] |= (!digitalRead(i)) << ((i - 22) % 8);
  }
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use 
  controllerData.analogAxisArray[0] = 512;
  controllerData.analogAxisArray[1] = 512; 
  controllerData.analogAxisArray[2] = 512; 
  controllerData.analogAxisArray[3] = 512; 
  controllerData.analogAxisArray[4] = 512; 
  controllerData.analogAxisArray[5] = 512; 
  controllerData.analogAxisArray[6] = 512; 
  controllerData.analogAxisArray[7] = 512; 
  controllerData.analogAxisArray[8] = 512; 
  controllerData.analogAxisArray[9] = 512; 
  controllerData.analogAxisArray[10] = 512; 
  controllerData.analogAxisArray[11] = 512; 
  
  // And return the data!
  return controllerData;
}
