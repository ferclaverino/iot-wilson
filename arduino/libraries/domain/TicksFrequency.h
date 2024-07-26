#ifndef TicksFrequency_h
#define TicksFrequency_h

#include "../time/TimeSpanMeasure.h"

class TicksFrequency {
public:
  float getFrequencyInHz(unsigned long currentTickCount, unsigned int timeSpanInMillis);
  void reset();
private:
  unsigned long _lastTickCount = 0;
  unsigned long getDifTickCount(unsigned long currentTickCount);
};

#endif