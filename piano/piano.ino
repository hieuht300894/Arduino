/*
 * 0: Unclick, 1: Click
 */
#define KEYS_NUMBER 32
#define KEY_OFF 1
#define KEY_ON 0
#define KEY_FIRST 22
#define KEY_LAST 53
#define MAX_TIME 100

byte curKeyState[KEYS_NUMBER];
byte lastKeyState[KEYS_NUMBER];
unsigned long timer = 0;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < KEYS_NUMBER; i++){
    byte keyID = i + KEY_FIRST;
      pinMode(keyID, INPUT_PULLUP);
      digitalWrite(keyID, KEY_OFF);
      curKeyState[i] = KEY_OFF;
      lastKeyState[i] = KEY_OFF;
  }
  //pinMode(2,INPUT_PULLUP);
}

void loop() {
//  bool isClick = digitalRead(2) == LOW ? true : false;
//
//  if (isClick && !lastClick)
//  {
//    Serial.println("One Click");
//    lastClick = isClick;
//  }
//  if (!isClick && lastClick)
//  {
//    Serial.println("Release");
//    lastClick = isClick;
//  }

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
      DisplayKeyStatus(keyID);
      isHaveNewValue = true;
    }
    if (curKey == KEY_OFF && lastKeyState[i] == KEY_ON){
      lastKeyState[i] = curKey;
    }
  }
  if (isHaveNewValue){ 
    Serial.println();
  }
}

void DisplayKeyStatus(byte keyID){
  Serial.print(keyID);
  Serial.print(" ");
}

