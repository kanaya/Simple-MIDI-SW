#include <MIDI.h>

const int LED0 = LED_BUILTIN;
const int LED1 = 11;
const int RLY  = 4;

MIDI_CREATE_DEFAULT_INSTANCE();

void hello() {
  for (int i = 0; i < 3; ++i) {
    delay(100);
    digitalWrite(LED0, HIGH);
    delay(100);
    digitalWrite(LED0, LOW);
  }
}

void turn_on() {
  digitalWrite(LED0, HIGH);
  digitalWrite(RLY, HIGH);  
}

void turn_off() {
    digitalWrite(LED0, LOW);
    digitalWrite(RLY, LOW);
}

void ignore_signal() {
  digitalWrite(LED1, HIGH);
  delay(50);
  digitalWrite(LED1, LOW);
}

// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// https://github.com/FortySevenEffects/arduino_midi_library/wiki/Using-Callbacks

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  if (pitch == 60) {
    if (velocity > 0) {
      turn_on();
    }
    else {
      turn_off();
    }
  }
  else {
    // ignore_signal();
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  if (pitch == 60) {
    turn_off();
  }
}

// -----------------------------------------------------------------------------

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(RLY, OUTPUT);
  hello();
  
  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);

  // Initiate MIDI communications, listen to ch 1
  MIDI.begin(1);
}

void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();
}
