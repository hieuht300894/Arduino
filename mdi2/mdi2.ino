#include <SoftwareSerial.h>

const int NOTE_WAIT = 254;
const int NOTE_START = 144;
const int NOTE_IGNORE = 176;
const int NOTE_FIRST = 28;
const int NOTE_LAST = 103;

const int NOTE_ON = 144; //144 = 10010000 in binary, note on command
const int NOTE_OFF = 128; //128 = 10000000 in binary, note off command

const int rxPin = 11;
const int txPin = 10; // not used

SoftwareSerial mySerial(rxPin, txPin);
int notes[NOTE_LAST - NOTE_FIRST + 1];
int note = 0;

//void setup()
//{
//    pinMode(rxPin, INPUT);
//    pinMode(txPin, OUTPUT);
//    Serial.begin(9600);
//    mySerial.begin(31250);
//}

//void loop()
//{
//  if (mySerial.available() > 0)
//  {
//    int incomingValue = mySerial.read();
//    if (incomingValue == NOTE_WAIT) {
//    }
//    else if (incomingValue == NOTE_IGNORE) {
//    }
//    else {
//      //      Serial.println(incomingValue);
//      if (incomingValue == NOTE_START) {
//        note = 0;
//      }
//      else {
//        if (note == 0) {
//          note = incomingValue;
//          if (note >= NOTE_FIRST && note <= NOTE_LAST) {
//            notes[note - NOTE_FIRST] = 0;
//          }
//        }
//        else {
//          if (note >= NOTE_FIRST && note <= NOTE_LAST) {
//            notes[note - NOTE_FIRST] = incomingValue;
//            if (incomingValue == 0)
//            {
//              //              Serial.print("Note ");
//              //              Serial.print(note);
//              //              Serial.println(" off");
//              MIDImessage(NOTE_OFF, note, incomingValue);
//            }
//            else
//            {
//              //              Serial.print("Note ");
//              //              Serial.print(note);
//              //              Serial.println(" on");
//              MIDImessage(NOTE_ON, note, incomingValue);
//            }
//          }
//          note = 0;
//        }
//      }
//    }
//  }
//}

void setup()
{
  Serial.begin(31250);
}

void loop()
{
  if (Serial.available() > 0)
  {
    int incomingValue = Serial.read();
    if (incomingValue == NOTE_WAIT) {
    }
    else if (incomingValue == NOTE_IGNORE) {
    }
    else {
      //      Serial.println(incomingValue);
      if (incomingValue == NOTE_START) {
        note = 0;
      }
      else {
        if (note == 0) {
          note = incomingValue;
          if (note >= NOTE_FIRST && note <= NOTE_LAST) {
            notes[note - NOTE_FIRST] = 0;
          }
        }
        else {
          if (note >= NOTE_FIRST && note <= NOTE_LAST) {
            notes[note - NOTE_FIRST] = incomingValue;
            if (incomingValue == 0)
            {
              //              Serial.print("Note ");
              //              Serial.print(note);
              //              Serial.println(" off");
              MIDImessage(NOTE_OFF, note, incomingValue);
            }
            else
            {
              //              Serial.print("Note ");
              //              Serial.print(note);
              //              Serial.println(" on");
              MIDImessage(NOTE_ON, note, incomingValue);
            }
          }
          note = 0;
        }
      }
    }
  }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}
