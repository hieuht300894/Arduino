int pin_Start  = 23;
int pin_Step = 2;
int pin_Total = 15;
int def_ValueStepLeft = 399;
int def_ValueStepRight = 611;
int def_ValueMin = 0;
int def_ValueCenter = 511;
int def_ValueMax = 1023;
int pin_Reset = 43;
int def_Normal = 0;
int def_Race = 1;
int pin_X_Axist = A1;
int pin_Y_Axist = A2;
int pin_Z_Axist = A3;
int pin_X_Rotation = A4;
int pin_Y_Rotation = A5;
int pin_Z_Rotation = A6;

/*Default: 1, 0: Normal, 1: Race*/
int mode = def_Normal;
/*Default: true, true: Release, false: Press*/
bool prev_Status = true;
/*Default: false, false: Stop, true: Start*/
bool is_Start = false;

int A1_ValueCenter = def_ValueCenter;
int A1_ValueError = def_ValueMin;
int A1_ValueError_2 = def_ValueMin;

int A2_ValueMax = def_ValueMax;
int A3_ValueMax = def_ValueMax;

void setup()
{
  Serial.begin(9600);
  setupPins();
  setupValues();

  is_Start = true;
}

void loop()
{
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

    getControllerData();
  }

  delay(500);
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
  A1_ValueCenter =  analogRead(pin_X_Axist);
  A1_ValueError = def_ValueCenter - A1_ValueCenter;
  A1_ValueError_2 = def_ValueCenter - map(A1_ValueCenter + A1_ValueError, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax);

  A2_ValueMax = analogRead(pin_Y_Axist);
  A3_ValueMax = analogRead(pin_Z_Axist);

  Serial.print("A1_ValueCenter: ");
  Serial.println(A1_ValueCenter);
  Serial.print("A1_ValueError: ");
  Serial.println(A1_ValueError);
  Serial.print("A1_ValueError_2: ");
  Serial.println(A1_ValueError_2);
  Serial.print("A2_ValueMax: ");
  Serial.println(A2_ValueMax);
  Serial.print("A3_ValueMax: ");
  Serial.println(A3_ValueMax);
}

void getControllerData() {
  int pin_Current = pin_Start;
  for (int i = 0; i < pin_Total; i++)
  {
    if (!(pin_Current == pin_Reset))
    {
      if (!digitalRead(pin_Current))
      {
        Serial.print("Key press: ");
        Serial.println(pin_Current);
      }
    }

    pin_Current += pin_Step;
  }

  Serial.print("X Axist: ");
  Serial.println(getValueXAxist());
  Serial.print("Y Axist: ");
  Serial.println(getValueYAxist());
  Serial.print("Z Axist: ");
  Serial.println(getValueZAxist());
}

int getValueXAxist() {
  int val = def_ValueCenter;
  if (mode == def_Normal)
    val = analogRead(pin_X_Axist) + A1_ValueError;
  else if (mode == def_Race) {
    int temp = analogRead(pin_X_Axist) + A1_ValueError;
    if (temp < def_ValueStepLeft)
      val = def_ValueMin;
    else if (temp > def_ValueStepRight)
      val = def_ValueMax;
    else
      val = map(temp, def_ValueStepLeft, def_ValueStepRight, def_ValueMin, def_ValueMax) + A1_ValueError_2;
  }

  return val;
}

int getValueYAxist() {
  //return analogRead(pin_Y_Axist);
  return map(analogRead(pin_Y_Axist), def_ValueMin, A2_ValueMax, def_ValueMin, def_ValueMax);
}

int getValueZAxist() {
  return analogRead(pin_Z_Axist);
  //return map(analogRead(pin_Z_Axist), def_ValueMin, A3_ValueMax, def_ValueMin, def_ValueMax);
}
