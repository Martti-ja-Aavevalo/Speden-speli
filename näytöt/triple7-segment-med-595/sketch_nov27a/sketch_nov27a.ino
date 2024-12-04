int DS_pin = 13;
int STCP_pin = 12;
int SHCP_pin = 8;

int reset;

int score = 0;

int dec_digits [10]{126, 48, 109, 121, 51, 91, 95, 112, 127, 123};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
}

void loop() {
  printNum(1);
  delay(100);

}

void printNum(bool b)
{
  if(b)
  {
    score++;
    Serial.println(score);
    int first = score % 10;
    int middle = (score / 10) % 10;
    int last = score / 100;

    digitalWrite(STCP_pin, LOW);
    shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[last]);
    shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[middle]);
    shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[first]);
    digitalWrite(STCP_pin, HIGH);
  }
  if(!b)
  {
    digitalWrite(STCP_pin, LOW);
    shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[0]);
    shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[0]);
    shiftOut(DS_pin, SHCP_pin, LSBFIRST, dec_digits[0]);
    digitalWrite(STCP_pin, HIGH);
  }
}
