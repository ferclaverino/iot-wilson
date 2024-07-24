#include "CaudalimeterSampler.h"

CaudalimeterSampler::CaudalimeterSampler(const unsigned int bufferSize, const unsigned int sampleRateInMillis) {
  _buffer = new CircularBuffer(bufferSize);
  _waitForSample = new Wait(sampleRateInMillis);
}

void CaudalimeterSampler::sample(const long value) {
  if (_waitForSample->done()) {
    _buffer->push(value);
    _frequency = (_buffer->getLast() - _buffer->getFirst());
  }
}

const unsigned int CaudalimeterSampler::getFrequency() {
  return _frequency;
}

void CaudalimeterSampler::reset() {
  _buffer->reset();
}
