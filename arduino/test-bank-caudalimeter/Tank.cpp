#include "Tank.h"
#include "TimeSpanMeasure.h"

Tank::Tank(const float minWaterLevelDistance, const float maxWaterLevelDiscance, const unsigned int volume_mL) {
  _minWaterLevelDistance = minWaterLevelDistance;
  _maxWaterLevelDiscance = maxWaterLevelDiscance;
  _volume_mL = volume_mL;
  // Assume tank is full
  _waterLevelDistance = _maxWaterLevelDiscance;
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

const bool Tank::isMaxLevel() {
  bool isMaxLevel = false;
  if (_waterLevelDistance <= _maxWaterLevelDiscance) {
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

const float Tank::getEmptiedFlowInMlPerMinute() {
  float time_s = getEmptiedTimeSpanInSeconds();
  if (time_s == 0) {
    return 0;
  }

  float volume_ml = (float)_volume_mL;
  float time_m = time_s / 60.0;

  return _volume_mL / time_m;
}

const float Tank::getEmptiedTimeSpanInSeconds() {
  if (_timeSpanMeasure.getInMillis() == 0) return 0;
  float time_s = (float)_timeSpanMeasure.getInMillis() / 1000.0;
  return time_s;
}
