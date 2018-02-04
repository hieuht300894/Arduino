#define MAXTIME 1000

unsigned long timer = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((unsigned long)(millis() - timer) > MAXTIME){
    timer = millis();
  }

  if (digitalRead(9) == HIGH){
    digitalWrite(9, LOW);
  }
  else{
    digitalWrite(9, HIGH);
  }
}
