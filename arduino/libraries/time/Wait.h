#ifndef Wait_h
#define Wait_h

class Wait {
public:
  Wait(const unsigned int waitTimeForLoopInmillis);
  Wait(const unsigned int waitTimeForLoopInmillis, const unsigned int waitTimeForStartInmillis);
  const bool done();
  const unsigned int getDoneTimeSpanInMillis();
  const unsigned int getInProgressTimeSpanInMillis();

private:
  unsigned int _waitTimeForLoopInmillis;
  unsigned int _waitTimeForStartInmillis;
  unsigned long _lastLoopTimestamp;
  unsigned long _lastLoopTimeSpan;
  bool _isDoneStart;

  const bool Wait::doneStart();
  const bool Wait::doneLoop();
};

#endif