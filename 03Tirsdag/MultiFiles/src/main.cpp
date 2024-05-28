#include <Arduino.h>
#include "printtext.h"

// put function declarations here:
int myFunction(int, int);
static String text = "hello world";

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  printText(text);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}