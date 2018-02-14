#include "UnoJoy.h"

#define pin_Start  22
#define pin_Step 2
#define pin_Total 15
#define def_ValueMinLeft 102
#define def_ValueMaxRight 152
#define def_ValueMin 0
#define def_ValueCenter 127
#define def_ValueMax 255
#define pin_Reset 42
#define def_Normal 0
#define def_Race 1
#define pin_leftStickX A1
#define pin_leftStickY A2
#define pin_rightStickX A3
#define pin_rightStickY A4
//Lên
#define pin_dpadUpOn 24
//Xuống
#define pin_dpadDownOn 28
// Trái
#define pin_dpadLeftOn 46
//Phải
#define pin_dpadRightOn 40
//Tam giác
#define pin_triangleOn 22
//Tròn
#define pin_circleOn 30
//Vuông
#define pin_squareOn 34
//Chéo
#define pin_crossOn 38
#define pin_l1On 36
#define pin_l2On 50
#define pin_r1On 32
#define pin_r2On 26
#define pin_selectOn 48
#define pin_startOn 44

/*Default: 1, 0: Normal, 1: Race*/
int mode = 1;
/*Default: true, true: Release, false: Press*/
bool prev_Status = true;
/*Default: false, false: Stop, true: Start*/
bool is_Start = false;

volatile int A1_ValueCenter = (volatile int)def_ValueCenter;
volatile int A1_ValueError = (volatile int)def_ValueMin;
volatile int A1_ValueError_2 = (volatile int)def_ValueMin;

volatile int A2_ValueCenter = (volatile int)def_ValueCenter;
volatile int A2_ValueError = (volatile int)def_ValueMin;
volatile int A2_ValueError_2 = (volatile int)def_ValueMin;

void setup() {
  setupPins();
  setupValues();
  setupUnoJoy();

  is_Start = true;
}

void loop() {
  // Always be getting fresh data
  if (is_Start)
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

    dataForController_t controllerData = getControllerData();
    setControllerData(controllerData);
  }
}

void setupPins(void) {
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
  A1_ValueCenter = analogRead(pin_leftStickX) >> 2;
  A1_ValueError = (volatile int)def_ValueCenter - A1_ValueCenter;
  A1_ValueError_2 = (volatile int)def_ValueCenter - map(A1_ValueCenter + A1_ValueError, (volatile int)def_ValueMinLeft, (volatile int)def_ValueMaxRight, (volatile int)def_ValueMin, (volatile int)def_ValueMax);

  A2_ValueCenter =  analogRead(pin_leftStickY) >> 2;
  A2_ValueError = (volatile int)def_ValueCenter - A2_ValueCenter;
  A2_ValueError_2 = (volatile int)def_ValueCenter - map(A2_ValueCenter + A2_ValueError, (volatile int)def_ValueMinLeft, (volatile int)def_ValueMaxRight, (volatile int)def_ValueMin, (volatile int)def_ValueMax);
}

dataForController_t getControllerData(void) {

  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins

  controllerData.dpadUpOn = !digitalRead(pin_dpadUpOn);
  controllerData.dpadDownOn = !digitalRead(pin_dpadDownOn);
  controllerData.dpadLeftOn = !digitalRead(pin_dpadLeftOn);
  controllerData.dpadRightOn = !digitalRead(pin_dpadRightOn);

  controllerData.triangleOn = !digitalRead(pin_triangleOn);
  controllerData.circleOn = !digitalRead(pin_circleOn);
  controllerData.squareOn = !digitalRead(pin_squareOn);
  controllerData.crossOn = !digitalRead(pin_crossOn);

  controllerData.l1On = !digitalRead(pin_l1On);
  controllerData.l2On = !digitalRead(pin_l2On);
  controllerData.r1On = !digitalRead(pin_r1On);
  controllerData.r2On = !digitalRead(pin_r2On);

  controllerData.selectOn = !digitalRead(pin_selectOn);
  controllerData.startOn = !digitalRead(pin_startOn);

  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use
  controllerData.leftStickX = getValuePinA1();
  controllerData.leftStickY = (volatile int)def_ValueCenter;
  controllerData.rightStickX = (volatile int)def_ValueCenter;
  controllerData.rightStickY = (volatile int)def_ValueCenter;
  // And return the data!
  return controllerData;
}

volatile int getValuePinA1() {
  volatile int val = (volatile int)def_ValueCenter;
  if (mode == def_Normal)
    val = (volatile int)(analogRead(pin_leftStickX) >> 2) + A1_ValueError;
  else if (mode == def_Race) {
    volatile int temp = (volatile int)(analogRead(pin_leftStickX) >> 2) + A1_ValueError;
    if (temp < (volatile int)def_ValueMinLeft)
      val = (volatile int)def_ValueMin;
    else if (temp > (volatile int)def_ValueMaxRight)
      val = (volatile int)def_ValueMax;
    else
      val = map(temp, (volatile int)def_ValueMinLeft, (volatile int)def_ValueMaxRight, (volatile int)def_ValueMin, (volatile int)def_ValueMax) + A1_ValueError_2;
  }

  return val;
}

volatile int getValuePinA2() {
  volatile int val = (volatile int)def_ValueCenter;
  if (mode == def_Normal)
    val = (volatile int)(analogRead(pin_leftStickY) >> 2) + A2_ValueError;
  else if (mode == def_Race) {
    volatile int temp = (volatile int)(analogRead(pin_leftStickY) >> 2) + A2_ValueError;
    if (temp < (volatile int)def_ValueMinLeft)
      val = (volatile int)def_ValueMin;
    else if (temp > (volatile int)def_ValueMaxRight)
      val = (volatile int)def_ValueMax;
    else
      val = map(temp, (volatile int)def_ValueMinLeft, (volatile int)def_ValueMaxRight, (volatile int)def_ValueMin, (volatile int)def_ValueMax) + A2_ValueError_2;
  }

  return val;
}
