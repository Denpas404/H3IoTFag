#include <Arduino.h>


// Define the LED pin
const int ledPin = 2;
const int switchPin = 27; // Switch pin

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



void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Declare the semaphore
  _semaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(_semaphore);

  // Declare the taskhandles
  task1Handle = NULL;
  task2Handle = NULL;
  task3Handle = NULL;

  // Declare the token
  task1Token = false;

  // Declare tasks
  xTaskCreate(task1, "Task 1", 2048, NULL, 1, &task1Handle);
  xTaskCreate(task2, "Task 2", 2048, NULL, 1, &task2Handle);
  xTaskCreate(task3, "Task 3", 2048, NULL, 999, &task3Handle);
}

void loop() {
  // Loop should never be used in FreeRTOS
}



// Task 1 
void task1(void *pvParameters) {
  while (1) {
    if (task1Token) {
      if (xSemaphoreTake(_semaphore, portMAX_DELAY) == pdTRUE) {
        Serial.println("Task 1 blinking LED");

        digitalWrite(ledPin, HIGH);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        digitalWrite(ledPin, LOW);
        vTaskDelay(7000 / portTICK_PERIOD_MS); 
        xSemaphoreGive(_semaphore);

      }
    } else {
      vTaskDelay(100 / portTICK_PERIOD_MS); 
    }
    vTaskPrioritySet(task2Handle, 2);
    vTaskPrioritySet(task1Handle, 1);
  }
}

// Task 2 
void task2(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(_semaphore, portMAX_DELAY) == pdTRUE) {
      Serial.println("Task 2 blinking LED");
      for (int i = 0; i < 20; i++) {
        digitalWrite(ledPin, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS); 
        digitalWrite(ledPin, LOW);
        vTaskDelay(500 / portTICK_PERIOD_MS); 
      }
      xSemaphoreGive(_semaphore);


    }
    vTaskPrioritySet(task1Handle, 2); 
    vTaskPrioritySet(task2Handle, 1); 
  }
}


// Task 3 
void task3(void *pvParameters) {
  pinMode(switchPin, INPUT_PULLUP);
  while (1) {
    if (digitalRead(switchPin) == LOW) { 
    task1Token = !task1Token; 
    Serial.print("Task state: " );
    Serial.println(String(task1Token));
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); 
  }
}