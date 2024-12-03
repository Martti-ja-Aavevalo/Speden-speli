#include "mainheader.h"  
#include <Arduino_FreeRTOS.h>
#include <Arduino.h>

void Buzzer( void *pvParameters );
const int buzzer = 10;
void setup() {
  
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT); 
  
  while (!Serial) { 
  }

  xTaskCreate(
    Buzzer
    ,  "Buzzer"  
    ,  128 
    ,  NULL
    ,  1  
    ,  NULL );
}

void loop()
{

}


void Buzzer(void *pvParameters)  
{
  (void) pvParameters;
  

  for (;;)
  {

  }

}