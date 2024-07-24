#ifndef TimeSpanMeasure_h
#define TimeSpanMeasure_h

enum Status {
  STARTED,
  STOPPED
};

class TimeSpanMeasure {
public:
  void start();
  void stop();
  const unsigned long getInMillis();

private:
  unsigned long _startTimestamp = 0;
  unsigned long _timeSpan = 0;
  Status _status = Status::STOPPED;
};

#endif