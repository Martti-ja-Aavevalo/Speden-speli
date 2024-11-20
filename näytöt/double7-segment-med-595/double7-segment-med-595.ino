int STCP_pin = 4;
int SHCP_pin = 2;
int DS_pin = 7;

int STCP_pin1 = 12;
int SHCP_pin1 = 8;
int DS_pin1 = 13;

int numero = 0;

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

int dec_digits[10] {0,1,2,3,4,5,6,7,8,9};

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
  DisplayNum(numero);
  delay(500);
  numero++;

}

void DisplayNum(int num)
{
  if(num == 99)
  {
    numero = 0;
  }
  DisplayDigitSmall(num % 10);
  DisplayDigitBig(num / 10);

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