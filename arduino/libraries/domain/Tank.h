#ifndef Tank_h
#define Tank_h

#include "../time/TimeSpanMeasure.h"

class Tank {
public:
  Tank(const float minWaterLevelDistance, const float maxWaterLevelDiscance, const unsigned int volume_mL);
  const float getWaterLevelDistance();
  const void setWaterLevelDistance(const float waterLevelDistance);
  const void setWaterLevelOnMax();
  const void setWaterLevelOnMin();

  const bool isMaxLevel();
  const bool isMinLevel();
  const float getEmptiedTimeSpanInSeconds();

private:
  float _minWaterLevelDistance;
  float _maxWaterLevelDistance;
  unsigned int _volume_mL;
  float _waterLevelDistance;
  TimeSpanMeasure _timeSpanMeasure;
};

#endif