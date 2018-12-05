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

    if(inputString == "f") {
      command_start_time = millis();
      sparki.moveForward();
      CommandItem forward = CommandItem('f', command_start_time);

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
