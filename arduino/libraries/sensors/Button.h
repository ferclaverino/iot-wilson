#ifndef Button_h
#define Button_h

#include "../time/Debounce.h"

class Button {
public:
  Button(const unsigned int pin, const unsigned int debounceTimeInmillis);
  void begin();
  boolean isOn();
  boolean isToggle();

private:
  unsigned int _pin;
  bool volatile _isOn = false;
  bool volatile _isToggle = false;
  Debounce* _debounce;

  void toggle();
  void read();
};

#endif