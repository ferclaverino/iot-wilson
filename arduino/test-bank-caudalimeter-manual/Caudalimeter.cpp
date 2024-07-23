#include "Caudalimeter.h"
#include "Arduino.h"

Caudalimeter::Caudalimeter(const unsigned int pin) {
  _pin = pin;
  reset();
}

void Caudalimeter::begin(const TickCallback tickCalback) {
  // pull up works with falling
  pinMode(_pin, INPUT_PULLUP);

  // The only way to pass pointer to member function as pointer to functiosn 
  // https://isocpp.org/wiki/faq/pointers-to-members#fnptr-vs-memfnptr-types
  attachInterrupt(digitalPinToInterrupt(_pin), tickCalback, FALLING);
}

void Caudalimeter::reset() {
  _tickCount = 0;
}

void Caudalimeter::tick() {
  _tickCount++;
}

unsigned long Caudalimeter::getTickCount() {
  return _tickCount;
}
