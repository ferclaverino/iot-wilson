#include "Arduino.h"
#include "Button.h"
#include "../time/Debounce.h"

Button::Button(const unsigned int pin, const  unsigned int debounceTimeInmillis) {
  _pin = pin;
  _debounce = new Debounce(debounceTimeInmillis);
}

void Button::begin() {
  pinMode(_pin, INPUT_PULLUP);
}

boolean Button::isOn() {
  read();
  return _isOn;
}

boolean Button::isToggle() {
  read();
  if (_isToggle) {
    _isToggle = false;
    return true;
  }
  return false;
}

void Button::read() {
  int pinValue = digitalRead(_pin);

  if (pinValue == LOW) {
    toggle();
  }
}

void Button::toggle() {
  if (_debounce->done()) {
    _isOn = !_isOn;
    _isToggle = true;
  }
}
