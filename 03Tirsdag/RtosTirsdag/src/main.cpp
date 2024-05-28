#include <Arduino.h>

//Defind the LED pin and switch pin
#define LED_PIN 2
#define SWITCH_PIN 3

//Define 3 taskhandle
TaskHandle_t Task1Handler;
TaskHandle_t Task2Handler;
TaskHandle_t Task3Handler;


//Define 3 task functions
void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);

//Define a semaphore
SemaphoreHandle_t xSemaphore;

//Define a token
bool token = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly: 
}

//Declare task1
void Task1(void *pvParameters)
{
  
}

//Declare task2
void Task2(void *pvParameters)
{
  
}

//Declare task3
void Task3(void *pvParameters)
{
  
}
