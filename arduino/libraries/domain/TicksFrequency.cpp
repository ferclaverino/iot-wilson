#include "TicksFrequency.h"

float TicksFrequency::getFrequencyInHz(unsigned long currentTickCount, unsigned int timeSpanInMillis)
{
  unsigned long difTickCount = getDifTickCount(currentTickCount);
  float timeSpanInSeconds = (float)timeSpanInMillis / 1000.0;
  float frequency = (float)difTickCount / timeSpanInSeconds;
  return frequency;
}

unsigned long TicksFrequency::getDifTickCount(unsigned long currentTickCount) {
  unsigned long difTickCount = currentTickCount - _lastTickCount;
  _lastTickCount = currentTickCount;
  return difTickCount;
}
