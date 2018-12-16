#include <Sparki.h>

#include "CommandStack.h"

#define STATE_FIND_OBJECT 0
#define STATE_TRACEBACK 1
#define STATE_DANCE 2

CommandStack stack;

bool finished = false;

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

void resetState()
{
  while(!stack.isEmpty()) {
    stack.pop();
  }

  CommandItem start('d', 0);
  stack.push(start);
  currentState = STATE_FIND_OBJECT;
  inputString = NULL;
}

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
        if(stack.back()->command == 'f' || stack.back()->command == 'b')
          stack.back()->cmd_length = diff;
        stack.push('f');
        
        Serial.println(millis());
        sparki.moveForward();
        oldTime = millis();
      }
      if(inputString == 'b') {
        if(stack.getSize() == 1)
          oldTime = millis();

        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f' || stack.back()->command == 'b')
          stack.back()->cmd_length = diff;
        stack.push('f');
        
        sparki.moveBackward();
        oldTime = millis();
      }
      if(inputString == 's') {
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f' || stack.back()->command == 'b')
          stack.back()->cmd_length = diff;
        
        stack.push('s');
        
        sparki.moveStop();
        oldTime = millis();
      }
      if(inputString == 'l') {
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f' || stack.back()->command == 'b')
          stack.back()->cmd_length = diff;

        stack.push('l');
        sparki.moveLeft(90);
        oldTime = millis();
      }
      if(inputString == 'r') {        
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f' || stack.back()->command == 'b')
          stack.back()->cmd_length = diff;

        stack.push('r');
        sparki.moveRight(90);
        oldTime = millis();
      }
      if(inputString == 'g') {
        sparki.moveStop();
        unsigned long newTime = millis();
        unsigned long diff = newTime - oldTime;
        if(stack.back()->command == 'f' || stack.back()->command == 'b')
          stack.back()->cmd_length = diff;
        
        sparki.gripperClose();
        delay(6000);
        sparki.gripperStop();
        if(stack.back()->command == 'r')
          sparki.moveLeft(180);
        else
          sparki.moveRight(180);

        currentState = STATE_TRACEBACK;
      }
      if(inputString == 'e') {
        sparki.moveStop();
        resetState();
      }

      if(inputString == 'm') {
        currentState = STATE_DANCE;
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
          delay(6000);
          sparki.gripperStop();

          //restart state and command stack
          resetState();

          sparki.moveForward(-4);
          finished = true;
          currentState = STATE_DANCE;
      }
    }
  }

  if(currentState == STATE_DANCE) {
    int moveDist = 10;
    sparki.moveRight(moveDist/2);
    sparki.moveLeft(moveDist);
    sparki.moveRight(moveDist);
    sparki.moveLeft(moveDist);
    sparki.moveRight(moveDist);
    sparki.moveLeft(moveDist);
    sparki.moveRight(moveDist/2);
    if(finished) {
      sparki.moveRight(180);
      sparki.moveForward(1);
      sparki.moveForward(-1);
      finished = false;
    } else {
      sparki.moveRight(360);
    }
    currentState = STATE_FIND_OBJECT;
  }

  delay(100);
}

















