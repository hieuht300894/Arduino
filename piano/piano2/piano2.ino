/*
 * 0: Unclick, 1: Click
 */
#define KEYS_NUMBER 32
#define KEY_OFF 1
#define KEY_ON 0
#define KEY_FIRST 22
#define KEY_LAST 53
#define MAX_TIME 50

#define KEY_A  0x04
#define KEY_B  0x05
#define KEY_LShift 0xe1
#define KEY_O  0x12
#define KEY_P  0x13

byte curKeyState[KEYS_NUMBER];
byte lastKeyState[KEYS_NUMBER];
unsigned long timer = 0;
uint8_t buf[8] = { 0 };   /* Keyboard report buffer */

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < KEYS_NUMBER; i++){
    byte keyID = i + KEY_FIRST;
    pinMode(keyID, INPUT_PULLUP);
    digitalWrite(keyID, KEY_OFF);
    curKeyState[i] = KEY_OFF;
    lastKeyState[i] = KEY_OFF;
  }
}

void loop() {
  if ((unsigned long)(millis() - timer) > MAX_TIME)
  {  
    CheckKeyStatus();
    timer = millis();
  }
}

void CheckKeyStatus(){
  bool isHaveNewValue = false;
  for (int i = 0; i < KEYS_NUMBER; i++){
    byte keyID = i + KEY_FIRST;
    byte curKey = digitalRead(keyID);
    if (curKey == KEY_ON && lastKeyState[i] == KEY_OFF){
      lastKeyState[i] = curKey;
      LoadKey(i);
    }
    else if (curKey == KEY_OFF && lastKeyState[i] == KEY_ON){
      lastKeyState[i] = curKey;
    }
  }
}

void LoadKey(int keyID){
  if (keyID == 0){
    buf[2] = KEY_A; 
  }
  if (keyID == 1){
    buf[2] = KEY_B; 
  }
  if (keyID == 2){
    buf[0] = KEY_LShift;
    buf[2] = KEY_O;
  }
  if (keyID == 3){
    buf[0] = KEY_LShift;
    buf[2] = KEY_P;
  }
  
  Serial.write(buf, 8); // Send keypress
  releaseKey();
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);  // Release key  
}

