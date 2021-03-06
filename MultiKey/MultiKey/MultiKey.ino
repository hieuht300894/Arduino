/* @file MultiKey.ino
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| #
*/

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long startTime;


void setup() {
  Serial.begin(9600);
  startTime = millis();
}


void loop() {
  if ( (millis()- startTime) > 100 ) {
    startTime = millis();
  }

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
  if (kpd.getKeys())
  {
    for (int i=0; i< LIST_MAX ; i++) // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged ) // Only find keys that have changed state.
      {
        switch (kpd.key[i].kstate) // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
        {  
          case RELEASED:
            Serial.print(kpd.key[i].kchar);
            break;
        }
      }
    }
  }
}  // End loop
