int STCP_pin = 4;
int SHCP_pin = 2;
int DS_pin = 7;

int STCP_pin1 = 12;
int SHCP_pin1 = 8;
int DS_pin1 = 13;

int bigNum = 10;
int num = 0;

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
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin1, OUTPUT);
  pinMode(SHCP_pin1, OUTPUT);
  pinMode(DS_pin1, OUTPUT);
  //pinMode(11, OUTPUT);
  Serial.begin(9600);
  //DisplayDigit(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  DisplayNum(1);
  delay(500);
}

void DisplayNum(bool b)
{
  if(b)
  { 
    num++;
    if(num == 99)
    {
      num = 0;
    }
    DisplayDigitSmall(num % 10);
    if(num == bigNum)
    {
      DisplayDigitBig(num / 10);
      bigNum += 10;
    }

  }
  if(!b)
  {
    num = 0;
    DisplayDigitSmall(0);
    DisplayDigitBig(0);
  }
}

void DisplayDigitBig(int Digit)
{
    digitalWrite(STCP_pin,LOW);
    for (int i = 8; i>=0; i--)
   {
    digitalWrite(SHCP_pin,LOW);
    Serial.println(digits[Digit][i]);
    if (digits[Digit][i]==1) digitalWrite(DS_pin, LOW); 
    if (digits[Digit][i]==0) digitalWrite(DS_pin, HIGH);
    digitalWrite(SHCP_pin,HIGH);
    //Serial.println(digits[Digit][i]);
   }
   digitalWrite(STCP_pin, HIGH); 
}
void DisplayDigitSmall(int Digit)
{
    digitalWrite(STCP_pin1,LOW);
    for (int i = 8; i>=0; i--)
   {
    digitalWrite(SHCP_pin1,LOW);
    Serial.println(digits[Digit][i]);
    if (digits[Digit][i]==1) digitalWrite(DS_pin1, LOW); 
    if (digits[Digit][i]==0) digitalWrite(DS_pin1, HIGH);
    digitalWrite(SHCP_pin1,HIGH);
    //Serial.println(digits[Digit][i]);
   }
   digitalWrite(STCP_pin1, HIGH); 
}