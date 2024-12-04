#include "mainheader.h"  
#include "Arduino.h"
#include "pitches.cpp"
int tempo = 122;



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
 };

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

void songCompiler(float songSpeed, int buzzer){


  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

}

