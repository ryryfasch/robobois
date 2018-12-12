#include <Sparki.h>

#include "CommandStack.h"

CommandStack stack;

unsigned long oldTime;

String inputString;

/* Instructions
 * Write code and upload to sparki via USB
 * Then open PuTTY and connect to COM10/COM11 and then code should run via bluetooth
 */

void setup() {
  // put your setup code here, to run once:
  // PuTTY serail port is COM10 or COM11
  Serial1.begin(9600);
  Serial.begin(9600);
  oldTime = millis();
  CommandItem start('d', 0);
  stack.push(start);
}

void loop() {
  if(Serial1.available()) {
    int inByte = Serial1.read();
    inputString += (char)inByte;
//    char* split = strtok(inputString," ");
//    while (split != NULL)
    {
//    Serial.println(split);
//    split = strtok (NULL, " ");
    }
//    Serial.println(split[0]);

    if(inputString == "f") {
      unsigned long newTime = millis();
      unsigned long diff = newTime - oldTime;
      stack.back()->cmd_length = diff;
      oldTime = millis();
      stack.push('f');
      Serial.print("Back command: "); Serial.print(stack.back()->command);
      Serial.print("   Length: ");  Serial.println(stack.back()->cmd_length);
      sparki.moveForward();
    }
    if(inputString == "s") {
      unsigned long newTime = millis();
      unsigned long diff = newTime - oldTime;
      stack.back()->cmd_length = diff;
      oldTime = millis();
      
      sparki.moveStop();
    }
    if(inputString == "l") {
      sparki.moveLeft(90);
    }
    if(inputString == "r") {
      sparki.moveRight(90);
    }
  }
  inputString = "";
}
