int aktviivinenledi = -1;         
int ledinviive = 1000; 
int ledishowviive = 200; 

void show1()
{
  for(int i = 0; i < 16; i++)
  {

  }
}

void setLed(byte pin) {
  digitalWrite(pin, HIGH);  
}

void clearAllLeds(void) {
  digitalWrite(A2, LOW);  
  digitalWrite(A3, LOW);  
  digitalWrite(A4, LOW);  
  digitalWrite(A5, LOW);  
}
void setAllLeds(void) {
  digitalWrite(A2, HIGH);  
  digitalWrite(A3, HIGH);  
  digitalWrite(A4, HIGH);  
  digitalWrite(A5, HIGH);  
}
void show2()
{
  for(int j = 0; j < 5; j++)
  {
    clearAllLeds();
    digitalWrite(A2, HIGH);
    delay(ledishowviive);
    digitalWrite(A3, HIGH);
    delay(ledishowviive);
    digitalWrite(A4, HIGH);
    delay(ledishowviive);
    digitalWrite(A5, HIGH);
    delay(ledishowviive);

    ledishowviive -= 30;
    if (ledishowviive < 50)
     {
      ledishowviive = 50;
    }
  }
   setAllLeds();
   delay(500);
   clearAllLeds();
}

void setup() {
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  show2();
}

void loop() {
  clearAllLeds();

  aktviivinenledi = random(0, 4);
  if (aktviivinenledi == 0) {
    setLed(A2); 
  } else if (aktviivinenledi == 1) {
    setLed(A3);  
  } else if (aktviivinenledi == 2) {
    setLed(A4);  
  } else if (aktviivinenledi == 3) {
    setLed(A5); 
  }
  delay(ledinviive); 
  clearAllLeds();
  if (ledinviive > 200) {
    ledinviive -= 50;
  }
  delay(200);  
}
