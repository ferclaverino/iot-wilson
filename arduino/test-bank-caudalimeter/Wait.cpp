#include "Arduino.h"
#include "Wait.h"

Wait::Wait(const unsigned int waitTimeForLoopInmillis) {
  Wait(waitTimeForLoopInmillis, 0);
}

Wait::Wait(const unsigned int waitTimeForLoopInmillis, const unsigned int waitTimeForStartInmillis) {
  _waitTimeForLoopInmillis = waitTimeForLoopInmillis;
  _waitTimeForStartInmillis = waitTimeForStartInmillis;
  _lastLoopTimestamp = 0;
  if (waitTimeForStartInmillis > 0) {
    _isDoneStart = false;
  }
  else {
    _isDoneStart = true;
  }
}

const bool Wait::done() {
  return (doneStart() && doneLoop());
}

const bool Wait::doneLoop() {
  const unsigned long nowTimestamp = millis();
  const unsigned long gap = nowTimestamp - _lastLoopTimestamp;
  bool isDone = false;

  if (gap > _waitTimeForLoopInmillis) {
    isDone = true;

    // Update last timestamp so difference between calls is > waitTimeInmillis
    _lastLoopTimestamp = nowTimestamp;
  }

  return isDone;
}

const bool Wait::doneStart() {
  if (_isDoneStart) return _isDoneStart;

  const unsigned long nowTimestamp = millis();
  if (nowTimestamp > _waitTimeForStartInmillis) {
    _isDoneStart = true;
  }

  return _isDoneStart;
}
