#ifndef PushButtonDigitalRead_h
#define PushButtonDigitalRead_h

#include "Arduino.h"
#include "Debounce.h"

typedef void(*ToggleCallback)();

class PushButtonDigitalRead {
public:
  PushButtonDigitalRead(const unsigned int pin, const unsigned int debounceTimeInmillis);
  void begin();
  boolean isPush();

private:
  unsigned int _pin;
  bool volatile _isPush = false;
  Debounce* _debounce;
  void toggle();
};

#endif