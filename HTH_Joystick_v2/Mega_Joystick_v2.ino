#include "MegaJoy.h"

#define pin_Start  22
#define pin_Step 2
#define pin_Total 15
#define def_ValueStepLeft 400
#define def_ValueStepRight 612
#define def_ValueMin 0
#define def_ValueCenter 512
#define def_ValueMax 1024
#define pin_Reset 42
#define def_Normal 0
#define def_Race 1
#define pin_X_Rotation A1
#define pin_Y_Rotation A2
#define pin_Z_Rotation A3

/*Default: 1, 0: Normal, 1: Race*/
int mode = 1;
/*Default: true, true: Release, false: Press*/
bool prev_Status = true;
/*Default: false, false: Stop, true: Start*/
bool is_Start = false;

int A1_ValueCenter = 512;
int A1_ValueError = 0;
int A1_ValueError_2 = 0;

int A2_ValueCenter = 512;
int A2_ValueError = 0;
int A2_ValueError_2 = 0;

int A3_ValueCenter = 512;
int A3_ValueError = 0;
int A3_ValueError_2 = 0;

void setup()
{
  setupPins();
  setupValues();
  setupMegaJoy();

  is_Start = true;
}

void loop()
{
  // Always be getting fresh data

  if (is_Start)
  {
    megaJoyControllerData_t controllerData = getControllerData();
    setControllerData(controllerData);
  }
}

void setupPins(void)
{
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the
  // two serial line pins

  int pin_Current = pin_Start;
  for (int i = 0; i < pin_Total; i++)
  {
    pinMode(pin_Current, INPUT);
    digitalWrite(pin_Current, HIGH);

    pin_Current += pin_Step;
  }
}

void setupValues() {
  A1_ValueCenter =  analogRead(pin_X_Rotation);
  A1_ValueError = def_ValueCenter - A1_ValueCenter;
  A1_ValueError_2 = def_ValueCenter - map(A1_ValueCenter + A1_ValueError, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax);

  A2_ValueCenter =  analogRead(pin_Y_Rotation);
  A2_ValueError = def_ValueCenter - A2_ValueCenter;
  A2_ValueError_2 = def_ValueCenter - map(A2_ValueCenter + A2_ValueError, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax);

  A3_ValueCenter =  analogRead(pin_Z_Rotation);
  A3_ValueError = def_ValueCenter - A3_ValueCenter;
  A3_ValueError_2 = def_ValueCenter - map(A3_ValueCenter + A3_ValueError, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax);
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

  int pin_Current = 22;
  for (int i = 0; i < pin_Total; i++)
  {
    if (pin_Current == pin_Reset)
    {
      if (digitalRead(pin_Reset) != prev_Status)
      {
        prev_Status = !prev_Status;
        if (!prev_Status)
        {
          if (mode == def_Normal)
            mode = def_Race;
          else  if (mode == def_Race)
            mode = def_Normal;

          is_Start = false;
          setupValues();
          is_Start = true;
        }
      }
    }
    else
    {
      controllerData.buttonArray[(pin_Current - pin_Start) / 8] |= (!digitalRead(pin_Current)) << ((pin_Current - pin_Start) % 8);
    }

    pin_Current += pin_Step;
  }

  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use
  // Use index 2,3,4,5
  //  controllerData.analogAxisArray[0] = 0;
  //  controllerData.analogAxisArray[1] = 0;
  //  controllerData.analogAxisArray[2] = 512;  // Z Axis
  //  controllerData.analogAxisArray[3] = analogRead(A1);  // X Rotation
  //  controllerData.analogAxisArray[4] = analogRead(A2);// Y Rotation
  //  controllerData.analogAxisArray[5] = analogRead(A3);// Z Rotation

  controllerData.analogAxisArray[0] = def_ValueCenter;
  controllerData.analogAxisArray[1] = def_ValueCenter;
  controllerData.analogAxisArray[2] = def_ValueCenter;  // Z Axis
  controllerData.analogAxisArray[3] = def_ValueCenter;  // X Rotation
  controllerData.analogAxisArray[4] = def_ValueCenter;// Y Rotation
  controllerData.analogAxisArray[5] = getValuePinA3();// Z Rotation

  // And return the data!
  return controllerData;
}

int getValuePinA1() {
  int val = def_ValueCenter;
  if (mode == def_Normal)
    val = analogRead(pin_X_Rotation) + A1_ValueError;
  else if (mode == def_Race) {
    int temp = analogRead(pin_X_Rotation) + A1_ValueError;
    if (temp < def_ValueStepLeft)
      val = def_ValueMin;
    else if (temp > def_ValueStepRight)
      val = def_ValueMax;
    else
      val = map(temp, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax) + A1_ValueError_2;
  }

  return val;
}

int getValuePinA2() {
  int val = def_ValueCenter;
  if (mode == def_Normal)
    val = analogRead(pin_Y_Rotation) + A2_ValueError;
  else if (mode == def_Race) {
    int temp = analogRead(pin_Y_Rotation) + A2_ValueError;
    if (temp < def_ValueStepLeft)
      val = def_ValueMin;
    else if (temp > def_ValueStepRight)
      val = def_ValueMax;
    else
      val = map(temp, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax) + A2_ValueError_2;
  }

  return val;
}

int getValuePinA3() {
  int val = def_ValueCenter;
  if (mode == def_Normal)
    val = analogRead(pin_Z_Rotation) + A3_ValueError;
  else if (mode == def_Race) {
    int temp = analogRead(pin_Z_Rotation) + A3_ValueError;
    if (temp < def_ValueStepLeft)
      val = def_ValueMin;
    else if (temp > def_ValueStepRight)
      val = def_ValueMax;
    else
      val = map(temp, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax) + A3_ValueError_2;
  }

  return val;
}
