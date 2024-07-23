#include "Relay.h"
#include "HCSR04.h"
#include "Tank.h"
#include "Wait.h"
#include "Caudalimeter.h"
#include "CaudalimeterSampler.h"
#include "PushButtonDigitalRead.h"
#include <math.h>

#define CAUDALIMETER_PIN 2
#define MAX_LEVEL_BUTTON_PIN 3
#define MIN_LEVEL_BUTTON_PIN 4
#define PUMP_RELAY_PIN 7
#define WATER_DISTANCE_TRIGGER_PIN 8
#define WATER_DISTANCE_ECHO_PIN 9

#define TANK_MIN_WATER_LEVEL_DISTANCE 19.0
#define TANK_MAX_WATER_LEVEL_DISTANCE 4.0
#define TANK_VOLUME 3000
#define TANK_WAIT_FOR_READ_DISTANCE 100

#define CAUDALIMETER_BUFFER_SIZE 60
#define CAUDALIMETER_SAMPLE_RATE 1000

#define BUTTON_DEBOUNCE_TIME 50

#define WAIT_FOR_PUBLISH_LOOP 1000
#define WAIT_FOR_PUBLISH_START 5000

// TODO: tank controller?
Relay pumpRelay(PUMP_RELAY_PIN);
HCSR04 waterDistance(WATER_DISTANCE_TRIGGER_PIN, WATER_DISTANCE_ECHO_PIN);
Tank tank(TANK_MIN_WATER_LEVEL_DISTANCE, TANK_MAX_WATER_LEVEL_DISTANCE, TANK_VOLUME);
Wait waitforReadDistance(TANK_WAIT_FOR_READ_DISTANCE);
PushButtonDigitalRead maxLevelButton(MAX_LEVEL_BUTTON_PIN, BUTTON_DEBOUNCE_TIME);
PushButtonDigitalRead minLevelButton(MAX_LEVEL_BUTTON_PIN, BUTTON_DEBOUNCE_TIME);

// TODO: caudalimeter controller?
Caudalimeter caudalimeter(CAUDALIMETER_PIN);
CaudalimeterSampler caudalimeterSampler(CAUDALIMETER_BUFFER_SIZE, CAUDALIMETER_SAMPLE_RATE);

Wait waitforPublish(WAIT_FOR_PUBLISH_LOOP, WAIT_FOR_PUBLISH_START);

void caudalimeterTick() {
  caudalimeter.tick();
}

void setup() {
  Serial.begin(9600);
  pumpRelay.begin();
  waterDistance.begin();
  caudalimeter.begin(caudalimeterTick);
}

bool isAutoMode = true;

void loop() {

  if (isAutoMode) {
    if (waitforReadDistance.done()) {
      // TODO this returns wrong distance some times and turn off pump at mid level
      tank.setWaterLevelDistance(waterDistance.getDistanceInCm());
    }
  }
  else {
    if (maxLevelButton.isPush()) {
      isAutoMode = false;
      tank.setWaterLevelOnMax();
    }
    else {
      isAutoMode = true;
    }

    if (minLevelButton.isPush()) {
      isAutoMode = false;
      tank.setWaterLevelOnMin();
    }
    else {
      isAutoMode = true;
    }
  }

  if (tank.isMinLevel()) {
    if (!pumpRelay.isOn()) {
      caudalimeter.reset();
      caudalimeterSampler.reset();
    }
    pumpRelay.on();
  }

  if (tank.isMaxLevel()) {
    if (pumpRelay.isOn()) {
      caudalimeter.reset();
      caudalimeterSampler.reset();
    }
    pumpRelay.off();
  }

  caudalimeterSampler.sample(caudalimeter.getTickCount());

  if (waitforPublish.done()) {
    noInterrupts();

    publishDebug(isAutoMode, tank, caudalimeter, caudalimeterSampler);

    interrupts();
  }

}

void publishDebug(bool isAutoMode, Tank tank, Caudalimeter caudalimeter, CaudalimeterSampler caudalimeterSampler) {
  Serial.print(isAutoMode);
  Serial.print(", ");

  Serial.print(tank.getWaterLevelDistance());
  Serial.print(", ");

  // Serial.print(tank.getEmptiedTimeSpanInSeconds());
  // Serial.print(", ");

  // Serial.print(tank.getEmptiedFlowInMlPerMinute());
  // Serial.print(", ");

  // Serial.print(caudalimeter.getTickCount());
  // Serial.print(", ");

  // 3000 ml -> 949 tick count
  // const float k = 3000.0 / 949.0;
  // const unsigned int volumeBasedOnTickCount = (int)round(caudalimeter.getTickCount() * k);
  // Serial.print(volumeBasedOnTickCount);
  // Serial.print(", ");

  // const unsigned int freq = caudalimeterSampler.getFrequency();
  // Serial.print(caudalimeterSampler.getFrequency());
  // Serial.print(", ");

  // const float flow = freq * k;
  // Serial.print(flow);
  // Serial.print(", ");

  // Serial.print("reference flow (ml/minute): ");
  // Serial.print(tank.getEmptiedFlowInMlPerMinute());

  // Serial.print(" caudalimeter frequency (cycles/minute): ");
  // Serial.print(caudalimeterSampler.getFrequency());

  Serial.println();
}
