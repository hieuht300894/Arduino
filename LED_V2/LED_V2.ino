#define DelayTime 50

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Delay(500);
  Serial.println("Reset$");
  Delay(500);
  Serial.println("Init$");
  Delay(500);
  Serial.println("Number:10$");
  Delay(500);
  Serial.println("Status$");
  Delay(500);
  Serial.println("Finish$");
}

void loop() {
  // put your main code here, to run repeatedly:
  Delay(500);
  Serial.print("Hello World$");
}

void Delay(const int delayTime){
  long int curTime = millis();
  while ((curTime + delayTime) > millis()) {}
}
