#include <Arduino_FreeRTOS.h>

volatile int painallukset;
int sensorValue;
// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  xTaskCreate(
    TaskAnalogRead
    ,  "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}


void TaskAnalogRead(void *pvParameters)  // This is a task.
{

  (void) pvParameters;
  for (;;){
    sensorValue = analogRead(A0);
    if(sensorValue > 0){
    Serial.print(painallukset);
    Serial.println("Pohjassa");
    painallukset++;
      }
    }
    delay(100);
    //vTaskDelay(1);
}
