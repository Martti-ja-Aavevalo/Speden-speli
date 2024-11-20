#include <Arduino_FreeRTOS.h>

volatile int painallukset;
int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue4;
char pressedPin;
int pressed = 0;
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
    sensorValue1 = analogRead(A0);
    sensorValue2 = analogRead(A1);
    //sensorValue3 = analogRead(A2);
    //sensorValue4 = analogRead(A2);
    if(sensorValue1 > 0){pressedPin = '1'; pressed = 1;}
    if(sensorValue2 > 0){pressedPin = '2'; pressed = 1;}
    if(sensorValue3 > 0){pressedPin = '3'; pressed = 1;}
    if(sensorValue4 > 0){pressedPin = '4'; pressed = 1;}


    if(pressed == 1){
    delay(120);
    Serial.print("Pressed pin: ");
    Serial.println(pressedPin);
    pressed = 0;
      }
    }
    //vTaskDelay(1);
}
