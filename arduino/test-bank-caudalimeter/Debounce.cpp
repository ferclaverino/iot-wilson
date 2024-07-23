#include "Arduino.h"
#include "Debounce.h"

Debounce::Debounce(const unsigned int debounceTimeInmillis) {
  _debounceTimeInmillis = debounceTimeInmillis;
  _lastTimestamp = 0;
}

bool Debounce::done() {
  const unsigned long nowTimestamp = millis();
  const unsigned long gap = nowTimestamp - _lastTimestamp;
  bool isDone = false;

  if (gap > _debounceTimeInmillis) {
    isDone = true;
  }

  // Update last timestamp so difference between bounces is > debounceTimeInmillis
  _lastTimestamp = nowTimestamp;

  return isDone;
}
