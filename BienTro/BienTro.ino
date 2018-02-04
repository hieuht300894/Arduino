int oldValue = -1;
int newValue = 0;
int shift = 0;//0: No shift, 1:Shift left, 2:Shift right
int deviation = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  newValue = map(analogRead(A0), deviation, 1023 - deviation, 0, 255);

  if (newValue == oldValue) {
    shift = 0;
  }
  else if (newValue > oldValue) {
    shift = 1;
    oldValue = newValue;
  }
  else {
    shift = 2;
    oldValue = newValue;
  }

  switch (shift) {
    case 0:  Serial.println("No shift");
      break;
    case 1:  Serial.println("Shift left");
      break;
    case 2:  Serial.println("Shift right");
      break;
  }

  delay(100);
}
