#include "mainheader.h"  
#include "Arduino.h"
#include "pitches.cpp"
int tempo = 122;


//Melodiaosuus käyttää pitches.cpp kansiota jossa jokaiselle nuotille annetaan oikeat nuotit
int melody[] = {
  //Eka säkeistö
    NOTE_A3, 12, NOTE_C3, 12, NOTE_D3, 9, NOTE_D3, 9, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 9, NOTE_F3, 9, NOTE_F3, 12, NOTE_G3, 12,
    NOTE_E3, 9, NOTE_E3, 9, NOTE_D3, 12, NOTE_C3, 12, NOTE_C3, 12, NOTE_D3, 4,
    NOTE_A3, 12, NOTE_C3, 12, NOTE_D3, 9, NOTE_D3, 9, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 9, NOTE_F3, 9, NOTE_F3, 12, NOTE_G3, 12,
    NOTE_E3, 9, NOTE_E3, 9, NOTE_D3, 12, NOTE_C3, 12, NOTE_D3, 4,
  //Toka säkeistö
    NOTE_A3, 12, NOTE_C3, 12, NOTE_D3, 9, NOTE_D3, 9, NOTE_D3, 12, NOTE_F3, 12, NOTE_G3, 9, NOTE_G3, 9, NOTE_G3, 12, NOTE_A3, 12,
    NOTE_AS3, 9, NOTE_AS3, 9, NOTE_A3, 12, NOTE_G3, 12, NOTE_A3, 12,
    NOTE_D3, 6, PAUSE, 11, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 9, NOTE_F3, 9, NOTE_G3, 9, NOTE_A3, 12,  
    NOTE_D3, 6, PAUSE, 11, NOTE_D3, 12, NOTE_F3, 12, NOTE_E3, 9, NOTE_E3, 9, NOTE_F3, 9, NOTE_D3, 12, NOTE_E3, 3, 
  //Kolmas säkeistö
    PAUSE, 11, NOTE_A3, 12, NOTE_C3, 12, NOTE_D3, 9, NOTE_D3, 9, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 9, NOTE_F3, 9, NOTE_F3, 12, NOTE_G3, 12,
    NOTE_E3, 9, NOTE_E3, 9, NOTE_D3, 12, NOTE_C3, 12, NOTE_C3, 12, NOTE_D3, 9, PAUSE, 11, NOTE_A3, 12, NOTE_C3, 12, NOTE_D3, 9, NOTE_D3, 9, NOTE_D3, 12,
    NOTE_E3, 12, NOTE_F3, 9, NOTE_F3, 9, NOTE_F3, 12, NOTE_G3, 12, NOTE_E3, 9, NOTE_E3, 9, NOTE_D3, 12, NOTE_C3, 12, NOTE_D3, 16,
    PAUSE, 12, NOTE_A3, 12, NOTE_C3, 12, NOTE_D3, 9, NOTE_D3, 9, NOTE_D3, 12, NOTE_F3, 12, NOTE_G3, 9, NOTE_G3, 9, NOTE_G3, 12, NOTE_A3, 12, 
    NOTE_AS3, 9, NOTE_AS3, 9, NOTE_A3, 12, NOTE_G3, 12, NOTE_A3, 12, NOTE_D3, 9, PAUSE, 11, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 9, NOTE_F3, 9,
    NOTE_G3, 9, NOTE_AS3, 9, NOTE_D3, 9, PAUSE, 11, NOTE_D3, 12, NOTE_F3, 9, NOTE_E3, 9, NOTE_E3, 9, NOTE_D3, 9, NOTE_CS4, 12, NOTE_D3, 9, NOTE_D3, 9,
    NOTE_E3, 9, NOTE_F3, 9, NOTE_F3, 12, NOTE_F3, 12, NOTE_G3, 9, NOTE_A3, 4, NOTE_F3, 12, NOTE_D3, 12, NOTE_A3, 9,
  // Neljäs säkeistö
    NOTE_AS3, 6, PAUSE, 11, NOTE_G3, 12, NOTE_D3, 12, NOTE_AS3, 6, PAUSE, 9, NOTE_E3, 12, NOTE_E3, 9, NOTE_D3, 6, NOTE_F3, 6, PAUSE, 11, NOTE_F3, 12,
    NOTE_G3, 12, NOTE_A3, 9, NOTE_A3, 9, NOTE_A3, 9, NOTE_AS3, 12, NOTE_A3, 12, PAUSE, 6, NOTE_G3, 9, NOTE_G3, 9, NOTE_G3, 9, NOTE_G3, 12, NOTE_A3, 9,
    PAUSE, 9, NOTE_A3, 9, NOTE_A3, 9, NOTE_A3, 9, NOTE_AS3, 12, NOTE_A3, 9, PAUSE, 6, NOTE_G3, 9, NOTE_F3, 9, NOTE_E3, 9, NOTE_D3, 10, PAUSE, 9,
    NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 6, NOTE_G3, 12, NOTE_A3, 12, NOTE_G3, 9, NOTE_F3, 9, NOTE_E3, 9, NOTE_F3, 9, NOTE_G3, 9, NOTE_A3, 9, NOTE_G3, 10,
    PAUSE, 9, NOTE_F3, 12, NOTE_G3, 12, NOTE_A3, 9, PAUSE, 9, NOTE_G3, 12, NOTE_F3, 12, NOTE_E3, 9, NOTE_F3, 9, NOTE_E3, 9, NOTE_D3, 6, NOTE_E3, 12,
    NOTE_C3, 12, NOTE_D3, 6,
  // Viies säkeistö
    NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 8, PAUSE, 11, NOTE_E3, 12, NOTE_F3, 12, NOTE_G3, 9, NOTE_F3, 9, NOTE_G3, 9, NOTE_A3, 9, NOTE_G3, 9, NOTE_F3, 9,
    NOTE_D3, 6, PAUSE 15, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 9, NOTE_G3, 9, NOTE_A3, 9, NOTE_AS3, 9, NOTE_D3, 9, NOTE_G3, 9, NOTE_F3, 6, NOTE_G3, 12,
    NOTE_E3, 12, NOTE_D3, 6, NOTE_E3, 12, NOTE_AS3, 12, NOTE_A3, 8, PAUSE, 8, NOTE_AS3, 9,
    NOTE_A3, 9, NOTE_A3, 9, NOTE_A3, 9, NOTE_A3, 12, NOTE_G3, 9, PAUSE, 6, NOTE_G3, 6, PAUSE, 6, NOTE_F3, 6, PAUSE, 6, NOTE_F3, 9, NOTE_G3, 9, NOTE_E3, 9,
    NOTE_D3, 6, PAUSE, 15, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 12, NOTE_A3, 6, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 12, NOTE_AS3, 6, NOTE_D3, 12, NOTE_D3, 12,
    NOTE_E3, 12, NOTE_F3, 12, NOTE_A3, 9, NOTE_A3, 9, NOTE_C3, 9, NOTE_A3, 12, NOTE_G3, 9, PAUSE, 6, NOTE_G3, 6, PAUSE, 6, NOTE_F3, 6, PAUSE, 6, NOTE_F3, 9,
    NOTE_G3, 9, NOTE_E3, 9, NOTE_D3, 6, PAUSE, 6, NOTE_D3, 6,
 };

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
//Lasketaan nuotin pituus millisekunteina
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

void songCompiler(float songSpeed, int buzzer){


  //Toistetaan melodian soinnut
  //Lista on "tuplana" koska siinä on nuotit plus niiden pituus
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    
    //tsekataan jokaisen nuotin pituus
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // jos pituus on yli 0 jatketaan normisti
      noteDuration = (wholenote) / divider;

    } else if (divider < 0) {
      // Pisteelliset nuotit kestävät 1.5x nopeammin kuin norminuotit
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; //Kerrotaan duration 1x5
    }

    //Nuotista soitetaan vain 90% (pieni tauko auttaa selventämään melodiaa)
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    //Odotetaan kunnes seuraava nuotti soitetaan
    delay(noteDuration);

    //Varmistetaan ettei ylimääräistä ääntä pääse kuulumaan
    noTone(buzzer);
  }

}

//alkuperäisen koodin linkki: https://github.com/robsoncouto/arduino-songs/tree/master