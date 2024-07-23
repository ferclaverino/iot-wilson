#include "Arduino.h"
#include "PushButtonDigitalRead.h"
#include "Debounce.h"

PushButtonDigitalRead::PushButtonDigitalRead(const unsigned int pin, const  unsigned int debounceTimeInmillis) {
  _pin = pin;
  _debounce = new Debounce(debounceTimeInmillis);
}

void PushButtonDigitalRead::begin() {
  pinMode(_pin, INPUT_PULLUP);
}

bool PushButtonDigitalRead::isPush() {
  int pinValue = digitalRead(_pin);

  if (pinValue == LOW) {
    toggle();
  }

  return _isPush;
}

void PushButtonDigitalRead::toggle() {
  if (_debounce->done()) {
    _isPush = !_isPush;
  }
}
