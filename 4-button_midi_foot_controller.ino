//4-button MIDI-footcontroller fo Line6 HX stomp
//version 1.0
//2021-08-08
//Mikko Nopanen

#include <MIDI.h>
#include <Wire.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int last1Val = 0;

int mode = 0; //0=red, 1=green
int midichannel = 1;

int footButton1 = 2;
int footButton2 = 3;
int footButton3 = 4;
int footButton4 = 5;
int fingerButton = 6;

int ledRed = 10;
int ledGreen = 11;
int buttonLed = 12;

boolean footButton1pressed = false;
boolean footButton2pressed = false;
boolean footButton3pressed = false;
boolean footButton4pressed = false;
boolean fingerButtonPressed = false;

void setup() {

  pinMode(footButton1, INPUT_PULLUP);
  pinMode(footButton2, INPUT_PULLUP);
  pinMode(footButton3, INPUT_PULLUP);
  pinMode(footButton4, INPUT_PULLUP);
  pinMode(fingerButton, INPUT_PULLUP);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buttonLed, OUTPUT);

  digitalWrite(footButton1, HIGH);
  digitalWrite(footButton2, HIGH);
  digitalWrite(footButton3, HIGH);
  digitalWrite(footButton4, HIGH);
  digitalWrite(fingerButton, HIGH);

  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(buttonLed, HIGH);

  MIDI.begin(MIDI_CHANNEL_OFF);

  MIDI.sendProgramChange(0, midichannel);

  delay(1000);
}

void loop() {

  if (digitalRead(fingerButton) == LOW) {
    if (mode < 1) {
      mode++;
    } else {
      mode = 0;
    }
    delay(1000);
  }

  switch (mode) {
    case 0:
      mode0();
      break;

    case 1:
      mode1();
      break;
  }
}

void mode0() {

  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, HIGH);

  // FOOTBUTTON 1 previous footswitch mode
  if (digitalRead(footButton1) == LOW) {
    MIDI.sendControlChange(71, 4, midichannel);
    delay(400);
  }

  // FOOTBUTTON 2 next footwitch mode
  if (digitalRead(footButton2) == LOW) {
    MIDI.sendControlChange(71, 5, midichannel);
    delay(400);
  }

  // FOOTBUTTON 3 Snapshot mode
  if (digitalRead(footButton3) == LOW) {
    MIDI.sendControlChange(71, 3, midichannel);
    delay(400);
  }

  // FOOTBUTTON 4 emulates FS4
  if (digitalRead(footButton4) == LOW) {
    MIDI.sendControlChange(52, 127, midichannel);
    delay(400);
  }

}

void mode1() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, HIGH);
}
