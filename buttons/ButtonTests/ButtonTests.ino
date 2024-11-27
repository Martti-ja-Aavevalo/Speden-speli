#include <Arduino_FreeRTOS.h>

const int Button1 = 2;
const int Button2 = 3;
const int Button3 = 4;
const int Button4 = 5;
int button1LastPressed = 0;
int button2LastPressed = 0;
int button3LastPressed = 0;
int button4LastPressed = 0;

int debounce = 300;

volatile int painallukset;

void setup() {
  
  Serial.begin(9600);

  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);

  xTaskCreate(
    ButtLogic
    ,  "ButtLogic"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );

 
}
void loop(){

}

void ButtLogic(void *pvParameters)  
{

  while(true)
    {
      unsigned long currentMillis1 = millis();


      if(digitalRead(Button1) == LOW && currentMillis1 - button1LastPressed > debounce)
      {
        button1LastPressed = currentMillis1; 
        Serial.println("Pressed pin: 1");
      }
      unsigned long currentMillis2 = currentMillis1;
      if(digitalRead(Button2) == LOW && currentMillis2 - button2LastPressed > debounce)
      {
        button2LastPressed = currentMillis2; 
        Serial.println("Pressed pin: 2");
      }
      unsigned long currentMillis3 = currentMillis2;
      if(digitalRead(Button3) == LOW && currentMillis3 - button3LastPressed > debounce)
      {
        button3LastPressed = currentMillis3; 
        Serial.println("Pressed pin: 3");
      }
      unsigned long currentMillis4 = currentMillis3;
      if(digitalRead(Button4) == LOW && currentMillis4 - button4LastPressed > debounce)
      {
        button4LastPressed = currentMillis4; 
        Serial.println("Pressed pin: 4");
      }

    }
    vTaskDelay((50 / portTICK_PERIOD_MS));
}
