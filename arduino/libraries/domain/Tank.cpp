#include "Tank.h"
#include "../time/TimeSpanMeasure.h"

Tank::Tank(const float minWaterLevelDistance, const float maxWaterLevelDiscance, const unsigned int volume_mL) {
  _minWaterLevelDistance = minWaterLevelDistance;
  _maxWaterLevelDistance = maxWaterLevelDiscance;
  _volume_mL = volume_mL;
  // Assume tank is full
  _waterLevelDistance = _maxWaterLevelDistance;
}

const float Tank::getWaterLevelDistance() {
  return _waterLevelDistance;
}

const void Tank::setWaterLevelDistance(const float waterLevelDistance) {
  _waterLevelDistance = waterLevelDistance;

  if (isMaxLevel()) {
    _timeSpanMeasure.start();
  }
  if (isMinLevel()) {
    _timeSpanMeasure.stop();
  }

}

const void Tank::setWaterLevelOnMax() {
  setWaterLevelDistance(_maxWaterLevelDistance);
}

const void Tank::setWaterLevelOnMin() {
  setWaterLevelDistance(_minWaterLevelDistance);
}

const bool Tank::isMaxLevel() {
  bool isMaxLevel = false;
  if (_waterLevelDistance <= _maxWaterLevelDistance) {
    isMaxLevel = true;
  }
  return isMaxLevel;
}

const bool Tank::isMinLevel() {
  bool isMinLevel = false;
  if (_waterLevelDistance >= _minWaterLevelDistance) {
    isMinLevel = true;
  }
  return isMinLevel;
}

const float Tank::getEmptiedTimeSpanInSeconds() {
  if (_timeSpanMeasure.getInMillis() == 0) return 0;
  float time_s = (float)_timeSpanMeasure.getInMillis() / 1000.0;
  return time_s;
}
