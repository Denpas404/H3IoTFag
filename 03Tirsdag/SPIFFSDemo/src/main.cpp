#include <Arduino.h>
#include <FS.h>
#include "SPIFFS.h"



// put function declarations here:


void setup() {
  Serial.begin(115200);

  Serial.println("Mounting SPIFFS"); // Mount SPIFFS file system

  bool success = SPIFFS.begin(true); // Format file system if not already formatted
  
  if (!success) { // If SPIFFS mount failed
    Serial.println("SPIFFS Mount Failed"); // Print error message
    return; // Return from setup function
  }

  File file = SPIFFS.open("/config.txt", "r"); // Open file for reading

  if (!file) { // If file open failed
    Serial.println("Failed to open file for reading"); // Print error message
    return; // Return from setup function
  }

  Serial.println("File Content:");

  while (file.available()) { // While there is data in the file
    Serial.write(file.read()); // Print the data
  }

  file.close(); // Close the file
}

void loop() {
  // put your main code here, to run repeatedly:  
}

// put function definitions here:
