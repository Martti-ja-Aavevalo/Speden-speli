#include <Arduino_FreeRTOS.h>

// LEDS AND BUTTONS
const int OrangeLed = A0;
const int GreenLed = A1;
const int YellowLed = A2;
const int BlueLed = A3;

const int OrangeButton = 2;
const int GreenButton = 3;
const int YellowButton = 4;
const int BlueButton = 5;

int RandomLed = 0;
int PreviousLed = 0;
int LedDelay = 1000;
int CorrectPresses = 0;

// TIMER AND SCORE
unsigned long Timer = 10000;
bool defeat = false;

unsigned long lastTimerUpdate = 0;
unsigned long lastLedTime = 0;

int Score = 0;

// ARRAYS
const int ButtonOrder_Size = 100;
int ButtonOrder[ButtonOrder_Size];
int CurrentB_Size = 0;

const int InputOrder_Size = 100;
int InputOrder[InputOrder_Size];
int CurrentI_Size = 0;

// DEBOUNCE
const int threshold = LOW; //low when pressed
unsigned long debounceDelay = 300;
unsigned long lastPressedO = 0;
unsigned long lastPressedG = 0;
unsigned long lastPressedY = 0;
unsigned long lastPressedB = 0;

const int ledPins[] = {OrangeLed, GreenLed, YellowLed, BlueLed};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

// tasks
void TaskHandleLED(void *pvParameters);
void TaskHandleInput(void *pvParameters);

// functions
void addNumber(int arrayID, int number);
void removeNumber(int arrayID, int index);
void CheckArrays();
void addButtonPress();

void setup() {
  Serial.begin(9600);

  // seed rng from analog input
  randomSeed(analogRead(A6));

  pinMode(OrangeLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);

  pinMode(OrangeButton, INPUT_PULLUP);
  pinMode(GreenButton, INPUT_PULLUP);
  pinMode(YellowButton, INPUT_PULLUP);
  pinMode(BlueButton, INPUT_PULLUP);

  xTaskCreate(TaskHandleLED, "LED Task", 128, NULL, 1, NULL);
  xTaskCreate(TaskHandleInput, "Input Task", 128, NULL, 1, NULL);
}

void loop() {
  // https://open.spotify.com/track/5A5sHRQoeJHzMULQGPLoOV?si=ce7a77f5fc0443cc
}

// LED TASK
void TaskHandleLED(void *pvParameters) {
  while (true) {
    if (defeat) {
      // Turn all leds on if defeat
      digitalWrite(OrangeLed, HIGH);
      digitalWrite(GreenLed, HIGH);
      digitalWrite(YellowLed, HIGH);
      digitalWrite(BlueLed, HIGH);
    } else {
      if (millis() - lastTimerUpdate >= 1000) 
      {
        lastTimerUpdate = millis();
        Timer -= 1000;

        if (Timer <= 0) {
          Serial.println("TIMER DEPLETED");
          defeat = true;
          Timer = 0;
        }
      }
      // Turn on random led
      if (millis() - lastLedTime >= LedDelay) {
        lastLedTime = millis();
        addButtonPress();
        CorrectPresses++;
        if(CorrectPresses >= 10)
        {
          LedDelay = max(200, LedDelay * 0.90); // delay decreaded 10% every 10 correct presses
          CorrectPresses = 0;
          Serial.println("Speeding up...");
        }
        /*Serial.print("LedDelay: ");
        Serial.println(LedDelay);
        Serial.print("Timer shit: ");
        Serial.println(millis() - Timer);*/
      }
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);  // task delay 100ms
  }
}

// BUTTON TASK
void TaskHandleInput(void *pvParameters) {
  while (true) {
    unsigned long currentMillis = millis();

    // Orange button
    if (digitalRead(OrangeButton) == threshold && currentMillis - lastPressedO > debounceDelay) {
      lastPressedO = currentMillis;
      addNumber(1, OrangeLed);
      CheckArrays();
      Timer = 10000;
    }

    // Green button
    if (digitalRead(GreenButton) == threshold && currentMillis - lastPressedG > debounceDelay) {
      lastPressedG = currentMillis;
      addNumber(1, GreenLed);
      CheckArrays();
      Timer = 10000;
    }

    // Yellow button
    if (digitalRead(YellowButton) == threshold && currentMillis - lastPressedY > debounceDelay) {
      lastPressedY = currentMillis;
      addNumber(1, YellowLed);
      CheckArrays();
      Timer = 10000;
    }

    // Blue button
    if (digitalRead(BlueButton) == threshold && currentMillis - lastPressedB > debounceDelay) {
      lastPressedB = currentMillis;
      addNumber(1, BlueLed);
      CheckArrays();
      Timer = 10000;
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);  // task delay 50ms
  }
}

void addButtonPress() {
  int newLed;
  do {
    newLed = ledPins[random(0, numLeds)];  
  } while (newLed == PreviousLed);

  digitalWrite(PreviousLed, LOW);
  digitalWrite(newLed, HIGH);

  PreviousLed = newLed;
  addNumber(0, newLed);
  /*Serial.print("Added new led: ");
  Serial.println(newLed);*/
}

void addNumber(int arrayID, int number) {
  if (arrayID == 0) {
    if (CurrentB_Size < ButtonOrder_Size) {
      ButtonOrder[CurrentB_Size++] = number;
    } else {
      Serial.println("ButtonOrder array is full!");
    }
  } else {
    if (CurrentI_Size < InputOrder_Size) {
      InputOrder[CurrentI_Size++] = number;
    } else {
      Serial.println("InputOrder array is full!");
    }
  }
}

void removeNumber(int arrayID, int index) {
  if (arrayID == 0 && index < CurrentB_Size) {
    for (int i = index; i < CurrentB_Size - 1; i++) {
      ButtonOrder[i] = ButtonOrder[i + 1];
    }
    CurrentB_Size--;
  } else if (arrayID == 1 && index < CurrentI_Size) {
    for (int i = index; i < CurrentI_Size - 1; i++) {
      InputOrder[i] = InputOrder[i + 1];
    }
    CurrentI_Size--;
  }
}

void CheckArrays() {
  if (CurrentB_Size > 0 && CurrentI_Size > 0) {
    if (ButtonOrder[0] == InputOrder[0]) {
      removeNumber(0, 0);
      removeNumber(1, 0);
      Serial.println("Nice!");
      Score++;
      Serial.print("Score: ");
      Serial.println(Score);
    } else {
      defeat = true;
      Serial.println("DEFEAT");
    }
  }
}

/*void ResetArrays() {
  CurrentB_Size = 0;
  CurrentI_Size = 0;
  Serial.print("Score: ");
  Serial.println(Score);
}*/
