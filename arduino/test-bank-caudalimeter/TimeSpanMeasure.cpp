#include "Arduino.h"
#include "TimeSpanMeasure.h"

void TimeSpanMeasure::start() {
  if (_status == Status::STOPPED) {
    _status = Status::STARTED;
    _startTimestamp = millis();
  }
}

void TimeSpanMeasure::stop()
{
  if (_status == Status::STARTED) {
    _status = Status::STOPPED;
    unsigned long endTimestamp = millis();
    _timeSpan = endTimestamp - _startTimestamp;
  }

}

const unsigned long TimeSpanMeasure::getInMillis() {
  return _timeSpan;
}
