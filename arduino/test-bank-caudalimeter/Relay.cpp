#include "Arduino.h"
#include "Relay.h"

Relay::Relay(const unsigned int pin) {
  _pin = pin;
  _isOn = false;
}

void Relay::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
}

void Relay::on() {
  if (_isOn) return;
  digitalWrite(_pin, LOW);
  _isOn = true;
}

void Relay::off() {
  if (!_isOn) return;
  digitalWrite(_pin, HIGH);
  _isOn = false;
}

const boolean Relay::isOn() {
  return _isOn;
}