#include "mainheader.h"  
#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "pitches.cpp"
#include "songCompiler.cpp"



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
    tone(buzzer, NOTE_A3);
    Serial.print("a");
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