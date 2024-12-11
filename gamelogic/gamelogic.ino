#include "mainheader.h"
#include <Arduino.h>
#include <EEPROM.h>

//Alpon näytöt
int STCP_pin1 = 12;
int SHCP_pin1 = 8;
int DS_pin1 = 13;

int digits [10][8]{
  {0,0,0,0,0,0,0,1}, // digit 0
  {0,1,0,0,1,1,1,1}, // digit 1
  {0,0,0,1,0,0,1,0}, // digit 2
  {0,0,0,0,0,1,1,0}, // digit 3
  {0,1,0,0,1,1,0,0}, // digit 4
  {0,0,1,0,0,1,0,0}, // digit 5
  {0,0,1,0,0,0,0,0}, // digit 6
  {0,0,0,0,1,1,1,1}, // digit 7
  {1,0,0,0,0,0,0,0}, // digit 8
  {0,0,0,0,0,1,0,0}  // digit 9
};

// LEDS AND BUTTONS
const int OrangeLed = A0;
const int GreenLed = A1;
const int YellowLed = A2;
const int BlueLed = A3;
const int SpeedUpLed = A4;

const int OrangeButton = 2;
const int GreenButton = 3;
const int YellowButton = 4;
const int BlueButton = 5;

const int StartButton = 6;
const int BuzzerPin = 7;

int RandomLed = 0;
int PreviousLed = 0, PreviousLed2 = 0, PreviousLed3 = 0;
int LedDelay = 1000;
int CorrectPresses = 0;
float MusicSpeed = 1;

// TIMER AND SCORE
unsigned long Timer = 10000;
bool defeat = false;
bool HardMode = false;//false

int LedShowDelay = 200;
bool LedShow2Reverse = false;

unsigned long lastTimerUpdate = 0;
unsigned long lastLedTime = 0;

int Score = 0;
int HighScore;
bool GameStarted = false;

const int EEPROM_ADDR = 0;

// ARRAYS
const int ButtonOrder_Size = 100;
int ButtonOrder[ButtonOrder_Size];
int CurrentB_Size = 0;

const int InputOrder_Size = 100;
int InputOrder[InputOrder_Size];
int CurrentI_Size = 0;

int ButtonInputAmount[ButtonOrder_Size];
int CurrentA_Size = 0;
int AmountArrayCurrent = 1;
int PreviousArray = 0;

// DEBOUNCE
const int threshold = LOW; //low when pressed
unsigned long debounceDelay = 300;
unsigned long lastPressedO = 0;
unsigned long lastPressedG = 0;
unsigned long lastPressedY = 0;
unsigned long lastPressedB = 0;
unsigned long lastPressedS = 0;

const int ledPins[] = {OrangeLed, GreenLed, YellowLed, BlueLed};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

// functions
void addNumber(int arrayID, int number);
void removeNumber(int arrayID, int index);
void CheckArrays();
void addButtonPress(int LedAmount);
void setAllLeds();
void clearAllLeds();
void LedShow2();
void LedShow1();

void setup() {
  Serial.begin(9600);

  // seed rng from analog input
  randomSeed(analogRead(A6));

  pinMode(OrangeLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(SpeedUpLed, OUTPUT);

  pinMode(OrangeButton, INPUT_PULLUP);
  pinMode(GreenButton, INPUT_PULLUP);
  pinMode(YellowButton, INPUT_PULLUP);
  pinMode(BlueButton, INPUT_PULLUP);

  pinMode(StartButton, INPUT_PULLUP);

  pinMode(STCP_pin1, OUTPUT);
  pinMode(SHCP_pin1, OUTPUT);
  pinMode(DS_pin1, OUTPUT);

  int SavedNum = 0;
  EEPROM.get(EEPROM_ADDR, SavedNum);
  HighScore = max(HighScore, SavedNum);
  Serial.print("Current High Score: ");
  Serial.println(HighScore);
  Serial.println("Press start!");
}

void loop() {

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
  //start button
  if (digitalRead(StartButton) == threshold && currentMillis - lastPressedS > debounceDelay) {
    lastPressedS = currentMillis;
    if(!GameStarted){
      ResetGame();
    }
  }
  if(GameStarted){
    LedLoop();
    songCompiler(MusicSpeed, BuzzerPin);
  }
  else{
    LedShow2();
  }
}

void ResetGame()
{
  int SavedNum = 0;
  CurrentB_Size = 0;
  CurrentI_Size = 0;
  CurrentA_Size = 0;
  int AmountArrayCurrent = 1;
  int PreviousArray = 0;
  Serial.print("Previous Score: ");
  Serial.println(Score);
  EEPROM.get(EEPROM_ADDR, SavedNum);
  HighScore = max(HighScore, SavedNum);
  HighScore = max(HighScore, Score);
  EEPROM.put(EEPROM_ADDR, HighScore);
  Serial.print("Current High Score: ");
  Serial.println(HighScore);
  Score = 0;
  Timer = 10000;
  LedDelay = 1000;
  CorrectPresses = 0;
  defeat = false;
  setAllLeds();
  delay(600);
  clearAllLeds();
  delay(600);

  GameStarted = true;
}

// LED
void LedLoop() {
  if(GameStarted && !defeat)
  {
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
      digitalWrite(SpeedUpLed, LOW);
      lastLedTime = millis();
      if(!HardMode)
      {
        addButtonPress(0);
      }
      else
      {
        int randomnum = random(1, (100 - Score));
        if(Score >= 100 || randomnum <= 50)
        {
          randomnum = random(1, (100 - (Score - 75)));
          if(Score >= 175 || randomnum <= 50)
          {
            addNumber(2, 3);
            addButtonPress(3);
          }
          else
          {
            addNumber(2, 2);
            addButtonPress(2);
          }
        }
        else
        {
          addNumber(2, 0);
          addButtonPress(0);
        }
      }
      CorrectPresses++;  
      if(CorrectPresses >= 10)
      {
        LedDelay = max(200, LedDelay * 0.90); // delay decreaded 10% every 10 correct presses
        CorrectPresses = 0;
        digitalWrite(SpeedUpLed, HIGH);
        Serial.println("Speeding up...");
      }
    }
  }else if (GameStarted && defeat){
    // Turn all leds on if defeat
    for(int i=0;i<3;i++)
    {
      setAllLeds();
      delay(300);
      clearAllLeds();
      delay(300);
    }
    LedShow1();
  }
}

void addButtonPress(int LedAmount) {
  if(GameStarted && !defeat){
    int newLed, newLed2, newLed3;
    if(LedAmount == 0){
      if(PreviousArray == 3)
      {
        do {
          newLed = ledPins[random(0, numLeds)];  
        } while (newLed == PreviousLed);
        digitalWrite(PreviousLed, LOW);
        digitalWrite(PreviousLed2, LOW);
        digitalWrite(PreviousLed3, LOW);
      }
      else if (PreviousArray == 2)
      {
        do {
          newLed = ledPins[random(0, numLeds)];  
        } while (newLed == PreviousLed);
        digitalWrite(PreviousLed, LOW);
        digitalWrite(PreviousLed2, LOW);
      }
      else
      {
        do {
          newLed = ledPins[random(0, numLeds)];  
        } while (newLed == PreviousLed);
        digitalWrite(PreviousLed, LOW);
      }
      digitalWrite(newLed, HIGH);
      PreviousLed = newLed;
      /*Serial.print("Added num: ");
      Serial.println(newLed);*/
      addNumber(0, newLed);
    }
    else if (LedAmount == 2) {
      if(PreviousArray == 3)
      {
        newLed = ledPins[random(0, numLeds)];  
        do {
          newLed2 = ledPins[random(0, numLeds)];
        } while (newLed == newLed2);
        digitalWrite(PreviousLed, LOW);
        digitalWrite(PreviousLed2, LOW);
        digitalWrite(PreviousLed3, LOW);
      }
      else if (PreviousArray == 2)
      {
        do {
          newLed = ledPins[random(0, numLeds)];  
        } while (newLed == PreviousLed || newLed == PreviousLed2);
        do {
          newLed2 = ledPins[random(0, numLeds)];
        } while (newLed == newLed2);
        digitalWrite(PreviousLed, LOW);
        digitalWrite(PreviousLed2, LOW);
      }
      else
      {
        newLed = ledPins[random(0, numLeds)]; 
        do {
          newLed2 = ledPins[random(0, numLeds)];
        } while (newLed == newLed2);
        digitalWrite(PreviousLed, LOW);
      }
      digitalWrite(newLed, HIGH);
      digitalWrite(newLed2, HIGH);
      PreviousLed = newLed;
      PreviousLed2 = newLed2;
      addNumber(0, newLed2);
      addNumber(0, newLed);
    }
    else if (LedAmount == 3)
    {
      if(PreviousArray == 3)
      {
        do {
          newLed = ledPins[random(0, numLeds)];
        } while (newLed == PreviousLed || newLed == PreviousLed2 || newLed == PreviousLed3);
        do {
          newLed2 = ledPins[random(0, numLeds)];
        } while (newLed == newLed2);
        do {
          newLed3 = ledPins[random(0, numLeds)];
        } while (newLed == newLed3 || newLed2 == newLed3);
        digitalWrite(PreviousLed, LOW);
        digitalWrite(PreviousLed2, LOW);
        digitalWrite(PreviousLed3, LOW);
      }
      else if (PreviousArray == 2)
      {
        newLed = ledPins[random(0, numLeds)];
        do {
          newLed2 = ledPins[random(0, numLeds)];
        } while (newLed == newLed2);
        do {
          newLed3 = ledPins[random(0, numLeds)];
        } while (newLed == newLed3 || newLed2 == newLed3);
        digitalWrite(PreviousLed, LOW);
        digitalWrite(PreviousLed2, LOW);
      }
      else
      {
        newLed = ledPins[random(0, numLeds)]; 
        do {
          newLed2 = ledPins[random(0, numLeds)];
        } while (newLed == newLed2);
        do {
          newLed3 = ledPins[random(0, numLeds)];
        } while (newLed == newLed3 || newLed2 == newLed3);
        digitalWrite(PreviousLed, LOW);
      }
      digitalWrite(newLed, HIGH);
      digitalWrite(newLed2, HIGH);
      digitalWrite(newLed3, HIGH);
      PreviousLed = newLed;
      PreviousLed2 = newLed2;
      PreviousLed3 = newLed3;
      addNumber(0, newLed3);
      addNumber(0, newLed2);
      addNumber(0, newLed);
    }
  }
}

void addNumber(int arrayID, int number) {
  if(GameStarted && !defeat){
    if (arrayID == 0) {
      if (CurrentB_Size < ButtonOrder_Size) {
        ButtonOrder[CurrentB_Size++] = number;
      } else {
        Serial.println("ButtonOrder array is full!");
      }
    } else if (arrayID == 1){
      if (CurrentI_Size < InputOrder_Size) {
        InputOrder[CurrentI_Size++] = number;
      } else {
        Serial.println("InputOrder array is full!");
      }
    } else {
      if (CurrentA_Size < InputOrder_Size) {
        ButtonInputAmount[CurrentA_Size++] = number;
        /*Serial.print("Added Array ");
        Serial.println(number);*/
      } else {
        Serial.println("ButtonInputAmount array is full!");
      }
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
  } else if (arrayID == 2 && index < CurrentA_Size) {
    /*Serial.print("Removed Array ");
    Serial.println(ButtonInputAmount[0]);*/
    for (int i = index; i < CurrentA_Size - 1; i++) {
      ButtonInputAmount[i] = ButtonInputAmount[i + 1];
    }
    CurrentA_Size--;
  }
}

void CheckArrays() {
  if(GameStarted && !defeat){
    if (CurrentB_Size > 0 && CurrentI_Size > 0) {
      if(!HardMode)
      {
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
      else
      {
        /*Serial.print("BIA: ");
        for(int i = 0; i < CurrentA_Size; i++){
          Serial.print(ButtonInputAmount[i]);
        }
        Serial.println();*/
        if(ButtonInputAmount[0] > 1){
          if(AmountArrayCurrent == ButtonInputAmount[0]){
            if(ButtonInputAmount[0] == 2)
            {
              if(InputOrder[0] == InputOrder[1]){
                defeat = true;
                Serial.print("DEFEAT, same inputs: ");
                Serial.print(InputOrder[0]);
                Serial.print(", ");
                Serial.println(InputOrder[1]);
              }
              /*Serial.print("Inputs: ");
              Serial.print(InputOrder[0]);
              Serial.print(", ");
              Serial.print(InputOrder[1]);
              Serial.print(" Buttons: ");
              Serial.print(ButtonOrder[0]);
              Serial.print(", ");
              Serial.println(ButtonOrder[1]);*/
              if(InputOrder[0] + InputOrder[1] == ButtonOrder[0] + ButtonOrder[1])
              {
                removeNumber(0, 0);
                removeNumber(1, 0);
                removeNumber(0, 0);
                removeNumber(1, 0);
                PreviousArray = ButtonInputAmount[0];
                removeNumber(2, 0);
                Serial.println("Nice!");
                Score++;
                Serial.print("Score: ");
                Serial.println(Score);
              } else {
                defeat = true;
                Serial.println("DEFEAT, incorrect inputs");
              }
            }
            else
            {
              if(InputOrder[0] == InputOrder[1] || InputOrder[0] == InputOrder[2] || InputOrder[2] == InputOrder[1]){
                defeat = true;
                Serial.println("DEFEAT, B3");
              }
              /*Serial.print("Inputs: ");
              Serial.print(InputOrder[0]);
              Serial.print(", ");
              Serial.print(InputOrder[1]);
              Serial.print(", ");
              Serial.print(InputOrder[2]);
              Serial.print(" Buttons: ");
              Serial.print(ButtonOrder[0]);
              Serial.print(", ");
              Serial.print(ButtonOrder[1]);
              Serial.print(", ");
              Serial.println(ButtonOrder[2]);*/
              if(InputOrder[0] + InputOrder[1] + InputOrder[2] == ButtonOrder[0] + ButtonOrder[1] + ButtonOrder[2])
              {
                removeNumber(0, 2);
                removeNumber(1, 2);
                removeNumber(0, 1);
                removeNumber(1, 1);
                removeNumber(0, 0);
                removeNumber(1, 0);
                PreviousArray = ButtonInputAmount[0];
                removeNumber(2, 0);
                Serial.println("Nice!");
                Score++;
                Serial.print("Score: ");
                Serial.println(Score);
              } else {
                defeat = true;
                Serial.println("DEFEAT, B3 2");
              }
            }
            AmountArrayCurrent = 1;
          } else {
            AmountArrayCurrent++;
            //Serial.println("AAC++");
          }
        }
        else
        {
          if (ButtonOrder[0] == InputOrder[0]) {
            removeNumber(0, 0);
            removeNumber(1, 0);
            PreviousArray = ButtonInputAmount[0];
            removeNumber(2, 0);
            Serial.println("Nice!");
            Score++;
            Serial.print("Score: ");
            Serial.println(Score);
          } else {
            defeat = true;
            Serial.println("DEFEAT, 1");
          }
        }
      }
    }
  }
}

// Jonnen ledit
void clearAllLeds() {
  digitalWrite(OrangeLed, LOW);  
  digitalWrite(YellowLed, LOW);  
  digitalWrite(BlueLed, LOW);  
  digitalWrite(GreenLed, LOW);  
}
void setAllLeds() {
  digitalWrite(OrangeLed, HIGH);  
  digitalWrite(YellowLed, HIGH);  
  digitalWrite(BlueLed, HIGH);  
  digitalWrite(GreenLed, HIGH);  
}
// ledshow 1
void LedShow1()
{
  for(int i = 0; i < 16; i++)
  { 
    if(i & (1 << 0)) {
      digitalWrite(OrangeLed, HIGH);
    } else {
      digitalWrite(OrangeLed, LOW);
    }
    if(i & (1 << 1)){
      digitalWrite(GreenLed, HIGH);
    } else {
      digitalWrite(GreenLed, LOW);
    }
    if(i & (1 << 2)){
      digitalWrite(YellowLed, HIGH);
    } else {
      digitalWrite(YellowLed, LOW);
    }
    if(i & (1 << 3)){
      digitalWrite(BlueLed, HIGH);
    } else {
      digitalWrite(BlueLed, LOW);
    }
    delay(300);
  }
  clearAllLeds();
  delay(LedShowDelay);
  GameStarted = false;
  delay(500);
}
// ledshow 2
void LedShow2()
{
  int Led1 = OrangeLed;
  int Led2 = GreenLed;
  int Led3 = YellowLed;
  int Led4 = BlueLed;
  //Serial.println("Running LED show...");
  if(!GameStarted)
  {
    if(LedShow2Reverse){
      Led1 = BlueLed;
      Led2 = YellowLed;
      Led3 = GreenLed;
      Led4 = OrangeLed;
    }else{
      Led1 = OrangeLed;
      Led2 = GreenLed;
      Led3 = YellowLed;
      Led4 = BlueLed;
    }
    LedShowDelay = 200;
    for (int j = 0; j < 5; j++)
    {
      clearAllLeds();
      digitalWrite(Led1, HIGH);
      if (digitalRead(StartButton) == threshold) return;
      delay(LedShowDelay);
      digitalWrite(Led2, HIGH);
      if (digitalRead(StartButton) == threshold) return;
      delay(LedShowDelay);
      digitalWrite(Led3, HIGH);
      if (digitalRead(StartButton) == threshold) return;
      delay(LedShowDelay);
      digitalWrite(Led4, HIGH);
      if (digitalRead(StartButton) == threshold) return;
      delay(LedShowDelay);

      LedShowDelay -= 30;
      if (LedShowDelay < 50)
      {
        LedShowDelay = 50;
      }
    }
    LedShow2Reverse = !LedShow2Reverse;
    setAllLeds();
    delay(500);
    clearAllLeds();
  }
}