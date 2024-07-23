#ifndef Debounce_h
#define Debounce_h

#include "Arduino.h"

class Debounce {
public:
  Debounce(const unsigned int debounceTimeInmillis);
  bool done();

private:
  unsigned int _debounceTimeInmillis;
  unsigned long _lastTimestamp;
};

#endif