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

/*Other*/
bool IsStart = false;
bool IsEnd = false;
unsigned long timer = 0;
int delayTime = 100;

void setup() {
  Serial.begin(9600);

  pinMode(IC1_pin_In_Mux, INPUT);
  pinMode(IC1_pin_Out_S0, OUTPUT);
  pinMode(IC1_pin_Out_S1, OUTPUT);
  pinMode(IC1_pin_Out_S2, OUTPUT);

  pinMode(IC2_pin_In_Mux, INPUT);
  pinMode(IC2_pin_Out_S0, OUTPUT);
  pinMode(IC2_pin_Out_S1, OUTPUT);
  pinMode(IC2_pin_Out_S2, OUTPUT);
}

void loop() {
  unsigned long curTimer = millis();
  if ((unsigned long)(curTimer - timer) > delayTime)
  {
    if (!IsStart && !IsEnd)
    {
      IsStart = true;
      IsEnd = false;
      IC1_UpdateMux();
      IC2_UpdateMux();
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

void IC1_UpdateMux () {
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(IC1_pin_In_Mux, LOW);
    digitalWrite(IC1_pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(IC1_pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(IC1_pin_Out_S2, HIGH && (i & B00000100));
    Serial.print(digitalRead(IC1_pin_In_Mux));
    Serial.print(" ");
  }
//  Serial.println();
}

void IC2_UpdateMux () {
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(IC2_pin_In_Mux, LOW);
    digitalWrite(IC2_pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(IC2_pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(IC2_pin_Out_S2, HIGH && (i & B00000100));
    Serial.print(digitalRead(IC2_pin_In_Mux));
    Serial.print(" ");
  }
  Serial.println();
}
