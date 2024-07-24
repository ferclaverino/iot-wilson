#ifndef HCSR04_h
#define HCSR04_h

class HCSR04 {
public:
  HCSR04(const unsigned int triggerPin, const unsigned int echoPin);
  void begin();
  const float getDistanceInCm();

private:
  unsigned int _triggerPin;
  unsigned int _echoPin;
  float microsecondsToCentimeters(long microseconds);
};

#endif