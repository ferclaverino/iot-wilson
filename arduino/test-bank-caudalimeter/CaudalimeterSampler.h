#ifndef CaudalimeterSampler_h
#define CaudalimeterSampler_h

#include "Wait.h"
#include "CircularBuffer.h"

class CaudalimeterSampler {
public:
  CaudalimeterSampler(const unsigned int bufferSize, const unsigned int sampleRateInMillis);
  void sample(const long value);
  void reset();
  const unsigned int getFrequency();

private:
  Wait* _waitForSample;
  CircularBuffer* _buffer;
  unsigned int _frequency;
};

#endif