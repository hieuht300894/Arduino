//Dùng board Arduino Uno r3 làm mạch gamepad, để chế bộ volant cho các game mô phỏng lái xe 
//Trong đó volant được mô phỏng bằng encoder, nối kênh A vào chân 2, kênh B vào chân 3
//Các Pedal được mô phỏng bằng chiếc áp, nối chân giữa chiếc áp vào các chân A0-A2 (được 3 pedal)
//Các phím bấm gamepad được nối vào các chân từ 4 đến 12 và A3, A5 (được 12 phím).
//Chân 0, 1 dành cho giao tiếp UART; 
//Chân 2 chạy ngắt ngoài sườn âm, nối với kênh A để đếm xung, đo tốc độ encoder; 
//Chân 3 nối kênh B, xèt chiều quay encoder
//Nếu độ phân giải encoder khác 20 xung/vòng thì sửa giá trị phân giải tại dòng lệnh int n = 20;

#include "UnoJoy.h"
const int encoderA = 2;  //Chân 2 nối vào kênh A encoder, đếm xung encoder
const int encoderB = 3;  //Chân 3 nối vào kênh B encoder, kiểm tra mức xung B
volatile int Pulse0 = 0;  //Biến đếm xung  
volatile int Pulse = 0;   //biến đếm xung quy đổi

int n = 20; //độ phân giải encoder (số xung/vòng), nếu encoder có độ phải khác 20 xung thì sửa lại thông số này.
int m, k; //hệ số quy đổi số xung

void setup(){
  setupPins();
  setupUnoJoy();
  m = (int)(255/(2.5*n));   
  k = (int)(1.25*n); 
}
  
void loop(){
  // Always be getting fresh data
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void Gocquay(){          
      if (digitalRead(encoderB)) Pulse0++; 
      else Pulse0--; 		
    if (Pulse0 > k) Pulse0 = k;
    if (Pulse0 < -k) Pulse0 = -k;   
    Pulse = m*Pulse0 + 128; 
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins
  for (int i = 2; i <= 12; i++){
    pinMode(i, INPUT_PULLUP);
}
  
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  attachInterrupt(0, Gocquay, FALLING); 
 }

dataForController_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
//  controllerData.triangleOn = !digitalRead(2);
//  controllerData.circleOn = !digitalRead(3);
  controllerData.squareOn = !digitalRead(4);
  controllerData.crossOn = !digitalRead(5);
  controllerData.dpadUpOn = !digitalRead(6);
  controllerData.dpadDownOn = !digitalRead(7);
  controllerData.dpadLeftOn = !digitalRead(8);
  controllerData.dpadRightOn = !digitalRead(9);
  controllerData.l1On = !digitalRead(10);
  controllerData.r1On = !digitalRead(11);
  controllerData.selectOn = !digitalRead(12);
  controllerData.circleOn = !digitalRead(A3);
  controllerData.startOn = !digitalRead(A4);
  controllerData.homeOn = !digitalRead(A5);
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  
  controllerData.leftStickX = Pulse; //Đọc góc quay volant encoder, thay cho chiếc áp
  controllerData.leftStickY = analogRead(A0) >> 2; 
  controllerData.rightStickX = analogRead(A1) >> 2;
  controllerData.rightStickY = analogRead(A2) >> 2; 

   // And return the data!
  return controllerData;
}
