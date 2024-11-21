int aktviivinenledi = -1;         
int ledinviive = 1000;  

void show1()
{
  
}
void show2()
{
  
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

void setup() {
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
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
