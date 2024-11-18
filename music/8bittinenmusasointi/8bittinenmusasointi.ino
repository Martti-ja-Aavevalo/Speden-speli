#include "mainheader.h"  
#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "pitches.cpp"

// define two tasks for Blink & AnalogRead
void Buzzer( void *pvParameters );
const int buzzer = 10;
// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  
  while (!Serial) { // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.

  }

  xTaskCreate(
    Buzzer
    ,  "Buzzer"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}


void Buzzer(void *pvParameters)  
{
  (void) pvParameters;
  

  for (;;)
  {
    tone(buzzer, NOTE_A3);
    delay(100);
    tone(buzzer, NOTE_B3);
    delay(100);
    tone(buzzer, NOTE_C3);
    delay(100);
    tone(buzzer, NOTE_D3);
    delay(100);
    tone(buzzer, NOTE_E3);
    delay(100);
    tone(buzzer, NOTE_C3);
    delay(100);
    tone(buzzer, NOTE_E3);
    delay(100);
  }

}