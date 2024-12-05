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


void setup() {
  // put your setup code here, to run once:
  pinMode(STCP_pin1, OUTPUT);
  pinMode(SHCP_pin1, OUTPUT);
  pinMode(DS_pin1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  displaynum(221);
  delay(10000);
}

void displaynum(int num)
{
  int first = num % 10;
  int middle = (num / 10) % 10;
  int last = num / 100; 
  digitalWrite(STCP_pin1,LOW);
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(SHCP_pin1,LOW);
    Serial.print(digits[last][i]);
    if (digits[last][i]==1) digitalWrite(DS_pin1, LOW);
    if (digits[last][i]==0) digitalWrite(DS_pin1, HIGH);
    digitalWrite(SHCP_pin1,HIGH);
  }
  Serial.println(" ");
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(SHCP_pin1,LOW);
    Serial.print(digits[middle][i]);
    if (digits[middle][i]==1) digitalWrite(DS_pin1, LOW);
    if (digits[middle][i]==0) digitalWrite(DS_pin1, HIGH);
    digitalWrite(SHCP_pin1,HIGH);
  }
  Serial.println(" ");
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(SHCP_pin1,LOW);
    Serial.print(digits[first][i]);
    if (digits[first][i]==1) digitalWrite(DS_pin1, LOW);
    if (digits[first][i]==0) digitalWrite(DS_pin1, HIGH);
    digitalWrite(SHCP_pin1,HIGH);
  }
  digitalWrite(STCP_pin1, HIGH); 
}
