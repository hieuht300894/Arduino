#define PinStart 22
#define PinEnd 32
#define DelayTime 50
void setup() {
  for (int i=PinStart;i<=PinEnd;i++){
   pinMode(i,OUTPUT);
  }
}

void loop() {
  HieuUng1();
  HieuUng2();
  HieuUng1();
  HieuUng2();
  HieuUng1();
  HieuUng2();
  HieuUng1();
  HieuUng2();
  
  HieuUng3();
  HieuUng6();
  HieuUng4();
  HieuUng5();
  HieuUng3();
  HieuUng6();
  HieuUng4();
  HieuUng5();
  HieuUng3();
  HieuUng6();
  HieuUng4();
  HieuUng5();

  HieuUng1();
  HieuUng2();
  HieuUng1();
  HieuUng2();
  HieuUng1();
  HieuUng2();
  HieuUng1();
  HieuUng2();
  
  HieuUng7();
  HieuUng8();
  HieuUng7();
  HieuUng8();
  HieuUng7();
  HieuUng8();
  HieuUng7();
  HieuUng8();
  HieuUng7();
  HieuUng8();
  HieuUng7();
  HieuUng8();

  HieuUng9();
  HieuUng2();
  HieuUng10();
  HieuUng2();
  HieuUng9();
  HieuUng2();
  HieuUng10();
}

void Delay(const int delayTime){
  long int curTime = millis();
  while ((curTime + delayTime) > millis()) {}
}

//Bat tat ca
void HieuUng1(){
  for (int i=PinStart;i<=PinEnd;i++){
   digitalWrite(i,HIGH);
  }
  Delay(DelayTime);
}

//Tat tat ca
void HieuUng2(){
  for (int i=PinStart;i<=PinEnd;i++){
   digitalWrite(i,LOW);
  }
  Delay(DelayTime);
}

//Bat lan luot
void HieuUng3(){
  for (int i=PinStart;i<=PinEnd;i++){
   digitalWrite(i,HIGH);
   Delay(DelayTime);
  }   
}

//Bat lan luot nguoc lai
void HieuUng4(){
  for (int i=PinEnd ;i>=PinStart;i--){
   digitalWrite(i,HIGH);
   Delay(DelayTime);
  }   
}

//Tat lan luot
void HieuUng5(){
  for (int i=PinStart;i<=PinEnd;i++){
   digitalWrite(i,LOW);
   Delay(DelayTime);
  }   
}

//Tat lan luot nguoc lai
void HieuUng6(){
  for (int i=PinEnd ;i>=PinStart;i--){
   digitalWrite(i,LOW);
   Delay(DelayTime);
  }   
}

//Bat led cham, tat led le
void HieuUng7(){
  for (int i=PinStart;i<=PinEnd;i++){
    if (i%2==0){
      digitalWrite(i,HIGH);
    }
    else{
      digitalWrite(i,LOW);
    }
  }
  Delay(DelayTime);
}

//Bat led le, tat led cham
void HieuUng8(){
  for (int i=PinStart;i<=PinEnd;i++){
    if (i%2==0){
      digitalWrite(i,LOW);
    }
    else{
      digitalWrite(i,HIGH);
    }
  }
  Delay(DelayTime);
}

//Duoi bat
void HieuUng9(){
  int ledEnd=PinEnd;
  while(ledEnd>PinStart){
    digitalWrite(PinStart,HIGH);
    Delay(DelayTime/2);
    int i=PinStart+1;
    while(i<ledEnd){
      digitalWrite(i,HIGH);
      Delay(DelayTime/2);
      digitalWrite(i-1,LOW);
      Delay(DelayTime/2);
      i++;
    }
    digitalWrite(i,HIGH);
    Delay(DelayTime/2);
    ledEnd--;
  }
}

//Duoi bat nguoc lai
void HieuUng10(){
  int ledStart=PinStart;
  while(ledStart<PinEnd){
    digitalWrite(PinEnd,HIGH);
    Delay(DelayTime/2);
    int i=PinEnd-1;
    while(i>=ledStart){
      digitalWrite(i,HIGH);
      Delay(DelayTime/2);
      digitalWrite(i+1,LOW);
      Delay(DelayTime/2);
      i--;
    }
    digitalWrite(i,HIGH);
    Delay(DelayTime/2);
    ledStart++;
  }
}




