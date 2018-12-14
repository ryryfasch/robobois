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
        if(stack.getSize() == 1)
          oldTime = millis();

        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f')
          stack.back()->cmd_length = diff;
        stack.push('f');
        
        Serial.println(millis());
        sparki.moveForward();
        oldTime = millis();
      }
      if(inputString == 's') {
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        stack.back()->cmd_length = diff;
        Serial.println(millis());
        
        sparki.moveStop();
        oldTime = millis();
      }
      if(inputString == 'l') {
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f')
          stack.back()->cmd_length = diff;

        stack.push('l');
        sparki.moveLeft(90);
        oldTime = millis();
      }
      if(inputString == 'r') {        
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f')
          stack.back()->cmd_length = diff;

        stack.push('r');
        sparki.moveRight(90);
        oldTime = millis();
      }
      if(inputString == 'g') {
        sparki.moveStop();
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f')
          stack.back()->cmd_length = diff;
        
        sparki.gripperClose();
        delay(5000);
        sparki.gripperStop();
        sparki.moveRight(180);
        currentState = STATE_TRACEBACK;
      }
      if(inputString == 'e') {
        sparki.moveStop();
        while(!stack.isEmpty()) {
          stack.pop();
          CommandItem start('d', 0);
          stack.push(start);
        }
        
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
          return;
        }
      }

      CommandItem cmd = stack.pop();
      
      currentTracebackTime = millis();
      totalTracebackTime = currentTracebackTime + cmd.cmd_length;

      // float iTraceBackTime = currentTracebackTime/1000.0f;
      // float cmdTraceBackLength = totalTracebackTime/1000.0f;


//      Serial.print("Command Length: ");   Serial.println(cmdTraceBackLength);
//      Serial.print("Traceback tiem: ");   Serial.println(iTraceBackTime);

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
      if(cmd.command == 'd') {
          sparki.moveStop();
          sparki.gripperOpen();
          delay(5000);
          sparki.gripperClose();

          //restart state and command stack
          CommandItem start('d', 0);
          stack.push(start);
          currentState = STATE_FIND_OBJECT; 
      }
    }
  }

  delay(100);
}








