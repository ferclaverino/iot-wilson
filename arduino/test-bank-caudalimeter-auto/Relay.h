#ifndef Relay_h
#define Relay_h

class Relay {
public:
  Relay(const unsigned int pin);
  void begin();
  void on();
  void off();
  const boolean isOn();

private:
  unsigned int _pin;
  boolean _isOn;
};

#endif