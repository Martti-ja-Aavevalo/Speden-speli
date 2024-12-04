#include <LiquidCrystal_I2C.h>
#include  <Wire.h>

LiquidCrystal_I2C lcd(0x27,  16, 2);

char Word[6] = {'H', 'e', 'l', 'l', 'o', '!'};

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  /*delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Hello world!");*/
  for(int i = 0; i < sizeof(Word); i++)
  {
    lcd.setCursor(i, 0);
    lcd.print(Word[i]);
    delay(500);
  }
  delay(1000);
  for(int i = 0; i < 16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  lcd.clear();
  delay(700);
}
