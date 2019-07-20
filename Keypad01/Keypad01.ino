/* Rows */
const byte R1 = 8;
const byte R2 = 9;
const byte R3 = 10;
const byte R4 = 11;

/* Columns */
const byte C1 = 5;
const byte C2 = 4;
const byte C3 = 3;
const byte C4 = 2;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.print("Setup start");
  
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  pinMode(R3, INPUT);
  pinMode(R4, INPUT);
  
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  
  digitalWrite(C1, HIGH);
  digitalWrite(C2, HIGH);
  digitalWrite(C3, HIGH);
  digitalWrite(C4, HIGH);
  
  Serial.print("Setup end");
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(keypad_4x4());
  keypad_4x4();
  delay(500);
}

void keypad_4x4() {
  Serial.println("====");
  digitalWrite(C1, HIGH);
  digitalWrite(C2, LOW);
  digitalWrite(C3, LOW);
  digitalWrite(C4, LOW);
  Serial.print(digitalRead(R1));
  Serial.print(" ");
  Serial.print(digitalRead(R2));
  Serial.print(" ");
  Serial.print(digitalRead(R3));
  Serial.print(" ");
  Serial.print(digitalRead(R4));
  Serial.println();

  digitalWrite(C1, LOW);
  digitalWrite(C2, HIGH);
  digitalWrite(C3, LOW);
  digitalWrite(C4, LOW);
  Serial.print(digitalRead(R1));
  Serial.print(" ");
  Serial.print(digitalRead(R2));
  Serial.print(" ");
  Serial.print(digitalRead(R3));
  Serial.print(" ");
  Serial.print(digitalRead(R4));
  Serial.println();

  digitalWrite(C1, LOW);
  digitalWrite(C2, LOW);
  digitalWrite(C3, HIGH);
  digitalWrite(C4, LOW);
  Serial.print(digitalRead(R1));
  Serial.print(" ");
  Serial.print(digitalRead(R2));
  Serial.print(" ");
  Serial.print(digitalRead(R3));
  Serial.print(" ");
  Serial.print(digitalRead(R4));
  Serial.println();
  
  digitalWrite(C1, LOW);
  digitalWrite(C2, LOW);
  digitalWrite(C3, LOW);
  digitalWrite(C4, HIGH);
  Serial.print(digitalRead(R1));
  Serial.print(" ");
  Serial.print(digitalRead(R2));
  Serial.print(" ");
  Serial.print(digitalRead(R3));
  Serial.print(" ");
  Serial.print(digitalRead(R4));
  Serial.println();
  
  return 0;
}
