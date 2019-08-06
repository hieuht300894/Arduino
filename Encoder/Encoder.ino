const int pin_interrupt = 0;
const int pin_A = 2;
const int pin_B = 3;

int pulse = 0;
int pulseMax = 0;
int pulseMin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(0, rotate, FALLING);
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(map(pulse, pulseMin, pulseMax, 0 , 1023));
}

void rotate() {
  if (digitalRead(pin_B) == LOW) {
    pulse++;
  } else {
    pulse--;
  }

  if (pulse > pulseMax) {
    pulseMax = pulse;
  } else if (pulse < pulseMin) {
    pulseMin = pulse;
  }
}
