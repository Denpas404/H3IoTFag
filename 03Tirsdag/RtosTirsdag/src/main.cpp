#include <Arduino.h>


// Define the LED pin
const int ledPin = 2; // LED pin
const int switchPin = 27; // Switch pin
int counter; // Counter

// Define semaphore
SemaphoreHandle_t _semaphore; 

// Define task handles
TaskHandle_t task1Handle;
TaskHandle_t task2Handle;
TaskHandle_t task3Handle;

// Define task
void task1(void *pvParameters);
void task2(void *pvParameters);
void task3(void *pvParameters);

// Define Token
bool task1Token;

// Setup function
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT); // Set the LED pin as output
  digitalWrite(ledPin, LOW); // Set the LED pin to low

  // Declare the semaphore
  _semaphore = xSemaphoreCreateBinary(); // Create the semaphore
  xSemaphoreGive(_semaphore); // Give the semaphore

  // Declare the taskhandles
  task1Handle = NULL;
  task2Handle = NULL;
  task3Handle = NULL;

  // Declare the token
  task1Token = false;

  // Declare tasks
  xTaskCreate(task1, "Task 1", 2048, NULL, 1, &task1Handle);
  xTaskCreate(task2, "Task 2", 2048, NULL, 1, &task2Handle);
  xTaskCreate(task3, "Task 3", 2048, NULL, 1, &task3Handle);
}

void loop() {
  // Loop should never be used in FreeRTOS
}



// Declare Task 1 
void task1(void *pvParameters) {
  while (1) {
    if (task1Token) { // Check if the task should run
      if (xSemaphoreTake(_semaphore, portMAX_DELAY) == pdTRUE) { // Take the semaphore, if it is available
        Serial.println("Task 1 blinking LED");
        digitalWrite(ledPin, HIGH); // Turn on the LED
        vTaskDelay(3000 / portTICK_PERIOD_MS); // Delay for 3 seconds
        digitalWrite(ledPin, LOW); // Turn off the LED
        vTaskDelay(7000 / portTICK_PERIOD_MS); // Delay for 7 seconds
        xSemaphoreGive(_semaphore); // Release the semaphore
      }
    } else {
      vTaskDelay(100 / portTICK_PERIOD_MS); 
    }   
  }
}

// Declare Task 2
void task2(void *pvParameters) {
  while (1) {  
    if (xSemaphoreTake(_semaphore, portMAX_DELAY) == pdTRUE) { // Take the semaphore, if it is available
      Serial.println("Task 2 blinking LED"); 
      for (int i = 0; i < 20; i++) {
        digitalWrite(ledPin, HIGH); 
        vTaskDelay(500 / portTICK_PERIOD_MS); 
        digitalWrite(ledPin, LOW);
        vTaskDelay(500 / portTICK_PERIOD_MS); 
        counter++;
        Serial.println(counter);
      }
      xSemaphoreGive(_semaphore); // Release the semaphore
    }    
  }
}

// Declare Task 3 
void task3(void *pvParameters) {
  pinMode(switchPin, PULLUP); // Set the switch pin as input
  while (1) {
    if (digitalRead(switchPin) == LOW) {  // Check if the switch is pressed
    task1Token = !task1Token;  // Toggle the token value     
  }
    vTaskDelay(100 / portTICK_PERIOD_MS); 
  }
}