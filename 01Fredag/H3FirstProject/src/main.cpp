#include <Arduino.h>

static int counter = 0; // Counter variable
volatile uint8_t buttonState = 0; // Button state variable

IRAM_ATTR void minISR(){ // Interrupt service routine
  buttonState++;
}



void setup() {
  pinMode(GPIO_NUM_2, OUTPUT); // Setup port for led
  pinMode(GPIO_NUM_27, INPUT_PULLUP); // Setup port for button, can not be undefinded, must be tired to "1"
  Serial.begin(115200); // Start serial communication
  Serial.println("Hello from setup!"); // Print message
  attachInterrupt(digitalPinToInterrupt(GPIO_NUM_27), minISR, FALLING); // Attach interrupt to button
}


void loop() { 
  if (buttonState)
  {
    counter++; // Increment counter
    Serial.print("Button pressed! Counter: "); // Print message
    Serial.println(counter); // Print counter value
    buttonState = 0; // Reset button state
  }
  vTaskDelay(100); // Delay 100ms
}


