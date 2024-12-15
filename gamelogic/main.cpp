#include "mainheader.h"  
#include "Arduino.h"
#include "pitches.cpp"
#include <avr/pgmspace.h>
int tempo = 122;



const int melody[] PROGMEM = {
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
    NOTE_D3, 6, PAUSE, 15, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 9, NOTE_G3, 9, NOTE_A3, 9, NOTE_AS3, 9, NOTE_D3, 9, NOTE_G3, 9, NOTE_F3, 6, NOTE_G3, 12,
    NOTE_E3, 12, NOTE_D3, 6, NOTE_E3, 12, NOTE_AS3, 12, NOTE_A3, 8, PAUSE, 8, NOTE_AS3, 9,
    NOTE_A3, 9, NOTE_A3, 9, NOTE_A3, 9, NOTE_A3, 12, NOTE_G3, 9, PAUSE, 6, NOTE_G3, 6, PAUSE, 6, NOTE_F3, 6, PAUSE, 6, NOTE_F3, 9, NOTE_G3, 9, NOTE_E3, 9,
    NOTE_D3, 6, PAUSE, 15, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 12, NOTE_A3, 6, NOTE_D3, 12, NOTE_E3, 12, NOTE_F3, 12, NOTE_AS3, 6, NOTE_D3, 12, NOTE_D3, 12,
    NOTE_E3, 12, NOTE_F3, 12, NOTE_A3, 9, NOTE_A3, 9, NOTE_C3, 9, NOTE_A3, 12, NOTE_G3, 9, PAUSE, 6, NOTE_G3, 6, PAUSE, 6, NOTE_F3, 6, PAUSE, 6, NOTE_F3, 9,
    NOTE_G3, 9, NOTE_E3, 9, NOTE_D3, 6, PAUSE, 6, NOTE_D3, 6,
 };

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

void songCompiler(float songSpeed, int buzzer, bool reset) {
  static int thisNote = 0;              // Current note being played
  static unsigned long previousMillis = 0; // Last time the note changed
  static bool isPlaying = false;        // Whether a note is currently playing
  static int noteDuration = 0;          // Duration of the current note

  if (reset) {
    // Reset all static variables
    thisNote = 0;
    previousMillis = 0;
    isPlaying = false;
    noTone(buzzer); // Stop any currently playing note
    return;
  }

  unsigned long currentMillis = millis();

  // If not playing a note, calculate and start the next one
  if (!isPlaying && thisNote < notes * 2) {
    // Calculate the note duration
    int currentNote = pgm_read_word(&melody[thisNote]);
    int divider = pgm_read_word(&melody[thisNote + 1]);
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // Increases the duration for dotted notes
    }

    // Play the note
    if (currentNote != 0) {
      tone(buzzer, currentNote, noteDuration * 0.9);
    }

    // Start timing the note
    previousMillis = currentMillis;
    isPlaying = true;
  }

  // Check if the note's duration has elapsed
  if (isPlaying && (currentMillis - previousMillis >= noteDuration * songSpeed)) {
    noTone(buzzer); // Stop the current note
    thisNote += 2;  // Move to the next note
    isPlaying = false;
  }

  // If all notes are played, reset for the next loop
  if (thisNote >= notes * 2) {
    thisNote = 0;
  }
}