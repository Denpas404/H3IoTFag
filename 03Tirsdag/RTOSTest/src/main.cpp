#include <Arduino.h>


/// @brief  prototype of the task functions
static void MyTask1(void* pvParameters);
static void MyTask2(void* pvParameters);
static void MyIdleTask(void* pvParameters);

void setup()
{  
  Serial.begin(115200);
  Serial.println(F("In Setup function"));

  /* Create two tasks with priorities 1 and 2. An idle task is also created, 
     which will be run when there are no tasks in RUN state */

  xTaskCreate(MyTask1, "Task1", 2048, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 2048, NULL, 2, NULL);
  xTaskCreate(MyIdleTask, "IdleTask", 2048, NULL, 0, NULL);
}

void loop()
{
  
}

/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
  while(1)
  {
    Serial.println(F("Task1"));
    vTaskDelay(1000);
  }
}

/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {    
    Serial.println(F("Task2"));
    vTaskDelay(1500);
  }
}

/* Idle Task with priority Zero */ 
static void MyIdleTask(void* pvParameters)
{
  while(1)
  {
    Serial.println(F("Idle state"));
    vTaskDelay(500);
  }
}