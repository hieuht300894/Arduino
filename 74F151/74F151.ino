int pin_Out_S0 = 5; //SO
int pin_Out_S1 = 4; //S1
int pin_Out_S2 = 3; //S2
int pin_In_Mux1 = 2; //~Z
bool IsStart = false;
bool IsEnd = false;
unsigned long timer = 0;
int delayTime = 100;

void setup() {
  Serial.begin(9600);
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  pinMode(pin_In_Mux1, INPUT);
}

void loop() {
  unsigned long curTimer = millis();
  if ((unsigned long)(curTimer - timer) > delayTime)
  {
    if (!IsStart && !IsEnd)
    {
      IsStart = true;
      IsEnd = false;
      updateMux1();
      IsStart = true;
      IsEnd = true;
    }
    else if (IsStart && IsEnd)
    {
      IsStart = false;
      IsEnd = false;
    }
    timer = curTimer;
  }
}

void updateMux1 () {
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(pin_In_Mux1, LOW);
    digitalWrite(pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (i & B00000100));
    Serial.print(digitalRead(pin_In_Mux1));
    Serial.print(" ");
  }
  Serial.println();
}
