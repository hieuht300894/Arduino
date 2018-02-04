#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you conect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 255;

void setup() {
  Serial.begin(57600);
  error = ps2x.config_gamepad(13, 11, 10, 12, true, true); //setup pins and settings:  GamePad(clock 7, command 2 , attention 6 , data 1 , Pressures?, Rumble?) check for error

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }

}

void loop() {
  /* You must Read Gamepad to get new values
    Read GamePad and set vibration values
    ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
    if you don't enable the rumble, use ps2x.read_gamepad(); with no values

    you should call this at least once a second
  */

  if (error == 1) //skip loop if no controller found
    return;

  else { //DualShock Controller
    getData();
  }
  delay(50);
}

void getData() {
  ps2x.read_gamepad(true, vibrate);

  if (ps2x.NewButtonState()) {
    DigitalButton();
    StickButton();
  }
}

void DigitalButton() {
  if (ps2x.ButtonPressed(PSB_SELECT)) {
    Serial.println("PSB_SELECT is being held");
  }
  if (ps2x.ButtonPressed(PSB_L3)) {
    Serial.println("PSB_L3 is being held");
  }
  if (ps2x.ButtonPressed(PSB_R3)) {
    Serial.println("PSB_R3 is being held");
  }
  if (ps2x.ButtonPressed(PSB_START)) {
    Serial.println("PSB_START is being held");
  }
  if (ps2x.ButtonPressed(PSB_PAD_UP)) {
    Serial.println("PSB_PAD_UP is being held");
  }
  if (ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
    Serial.println("PSB_PAD_RIGHT is being held");
  }
  if (ps2x.ButtonPressed(PSB_PAD_DOWN)) {
    Serial.println("PSB_PAD_DOWN is being held");
  }
  if (ps2x.ButtonPressed(PSB_PAD_LEFT)) {
    Serial.println("PSB_PAD_LEFT is being held");
  }
  if (ps2x.ButtonPressed(PSB_L2)) {
    Serial.println("PSB_L2 is being held");
  }
  if (ps2x.ButtonPressed(PSB_R2)) {
    Serial.println("PSB_R2 is being held");
  }
  if (ps2x.ButtonPressed(PSB_L1)) {
    Serial.println("PSB_L1 is being held");
  }
  if (ps2x.ButtonPressed(PSB_R1)) {
    Serial.println("PSB_R1 is being held");
  }
  if (ps2x.ButtonPressed(PSB_GREEN)) {
    Serial.println("PSB_GREEN is being held");
  }
  if (ps2x.ButtonPressed(PSB_RED)) {
    Serial.println("PSB_RED is being held");
  }
  if (ps2x.ButtonPressed(PSB_BLUE)) {
    Serial.println("PSB_BLUE is being held");
  }
  if (ps2x.ButtonPressed(PSB_PINK)) {
    Serial.println("PSB_PINK is being held");
  }
  if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
    Serial.println("PSB_TRIANGLE is being held");
  }
  if (ps2x.ButtonPressed(PSB_CIRCLE)) {
    Serial.println("PSB_CIRCLE is being held");
  }
  if (ps2x.ButtonPressed(PSB_CROSS)) {
    Serial.println("PSB_CROSS is being held");
  }
  if (ps2x.ButtonPressed(PSB_SQUARE)) {
    Serial.println("PSB_SQUARE is being held");
  }
}

void AnalogButton() {
  if (ps2x.ButtonPressed(PSAB_PAD_RIGHT))
  {
    Serial.println("PSAB_PAD_RIGHT is being held");
  }
  if (ps2x.ButtonPressed(PSAB_PAD_UP))
  {
    Serial.println("PSAB_PAD_UP is being held");
  }
  if (ps2x.ButtonPressed(PSAB_PAD_DOWN))
  {
    Serial.println("PSAB_PAD_DOWN is being held");
  }
  if (ps2x.ButtonPressed(PSAB_PAD_LEFT))
  {
    Serial.println("PSAB_PAD_LEFT is being held");
  }
  if (ps2x.ButtonPressed(PSAB_L2))
  {
    Serial.println("PSAB_L2 is being held");
  }
  if (ps2x.ButtonPressed(PSAB_R2))
  {
    Serial.println("PSAB_R2 is being held");
  }
  if (ps2x.ButtonPressed(PSAB_L1))
  {
    Serial.println("PSAB_L1 is being held");
  }
  if (ps2x.ButtonPressed(PSAB_R1))
  {
    Serial.println("PSAB_R1 is being held");
  }
  if (ps2x.ButtonPressed(PSAB_GREEN))
  {
    Serial.println("PSAB_GREEN is being held");
  }
  if (ps2x.ButtonPressed(PSAB_RED))
  {
    Serial.println("PSAB_RED is being held");
  }
  if (ps2x.ButtonPressed(PSAB_BLUE))
  {
    Serial.println("PSAB_BLUE is being held");
  }
  if (ps2x.ButtonPressed(PSAB_PINK))
  {
    Serial.println("PSAB_PINK is being held");
  }
  if (ps2x.ButtonPressed(PSAB_TRIANGLE))
  {
    Serial.println("PSAB_TRIANGLE is being held");
  }
  if (ps2x.ButtonPressed(PSAB_CIRCLE))
  {
    Serial.println("PSAB_CIRCLE is being held");
  }
  if (ps2x.ButtonPressed(PSAB_CROSS))
  {
    Serial.println("PSAB_CROSS is being held");
  }
  if (ps2x.ButtonPressed(PSAB_SQUARE))
  {
    Serial.println("PSAB_SQUARE is being held");
  }

}

void StickButton() {
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
  {
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);
  }
}

