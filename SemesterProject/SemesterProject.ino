#include <Sparki.h>

#include "CommandStack.h"

String inputString;

/* Instructions
 * Write code and upload to sparki via USB
 * Then open PuTTY and connect to COM10/COM11 and then code should run via bluetooth
 */

void setup() {
  // put your setup code here, to run once:
  // PuTTY serail port is COM10 or COM11
  Serial1.begin(9600);
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
      CommandItem forward = CommandItem('f', NULL);
      sparki.moveForward();
    }
    if(inputString == "s") {
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
