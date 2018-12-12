#include <Sparki.h>

#include "CommandStack.h"

#define STATE_FIND_OBJECT 0
#define STATE_TRACEBACK 1

CommandStack stack;

unsigned long oldTime;

int currentState = STATE_FIND_OBJECT;

unsigned long totalTracebackTime;
unsigned long currentTracebackTime;
bool tracebackTimeSet = false;

char inputString;

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
  sparki.gripperOpen();
  delay(3000);
  sparki.gripperStop();
}

void loop() {
  if(currentState == STATE_FIND_OBJECT) {
    if(Serial1.available()) {
      int inByte = Serial1.read();
      inputString = (char)inByte;
  //    char* split = strtok(inputString," ");
  //    while (split != NULL)
      // {
  //    Serial.println(split);
  //    split = strtok (NULL, " ");
      // }
  //    Serial.println(split[0]);

      if(inputString == 'f') {
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f')
          stack.back()->cmd_length = diff;
        oldTime = millis();
        stack.push('f');
        sparki.moveForward();
      }
      if(inputString == 's') {
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        stack.back()->cmd_length = diff;
        oldTime = millis();
        
        sparki.moveStop();
      }
      if(inputString == 'l') {
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f')
          stack.back()->cmd_length = diff;
        oldTime = millis();
        stack.push('l');
        sparki.moveLeft(90);
      }
      if(inputString == 'r') {        
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f')
          stack.back()->cmd_length = diff;
        oldTime = millis();
        stack.push('r');
        sparki.moveRight(90);
      }
      if(inputString == 'g') {
        sparki.gripperClose();
        delay(3000);
        sparki.gripperStop();
        sparki.moveRight(180);
        currentState = STATE_TRACEBACK;
      }
    }
    inputString = NULL;
  }

  if(currentState == STATE_TRACEBACK) {
    if(!stack.isEmpty()) {
      currentTracebackTime = millis();
      if(tracebackTimeSet) {
        if(currentTracebackTime >= totalTracebackTime) {
          sparki.moveStop();
        } else {
          delay(100);
          return;
        }
      }

      CommandItem cmd = stack.pop();
      
      totalTracebackTime = currentTracebackTime + cmd.cmd_length;

      if(cmd.cmd_length > 0)
        tracebackTimeSet = true;
      else
        tracebackTimeSet = false;

      if(cmd.command == 'l') {
        sparki.moveRight(90);
      }
      if(cmd.command == 'r') {
        sparki.moveLeft(90);
      }
      if(cmd.command == 'f') {
        sparki.moveForward();
      }
      if(cmd.command == 's') {
        sparki.moveStop();
      }
    }
  }

  delay(100);
}

