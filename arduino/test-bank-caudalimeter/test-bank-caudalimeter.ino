#include "Relay.h"
#include "HCSR04.h"
#include "Tank.h"
#include "Wait.h"
#include "Caudalimeter.h"
#include "CaudalimeterSampler.h"
#include <math.h>

#define CAUDALIMETER_PIN 2
#define PUMP_RELAY_PIN 7
#define WATER_DISTANCE_TRIGGER_PIN 8
#define WATER_DISTANCE_ECHO_PIN 9

#define TANK_MIN_WATER_LEVEL_DISTANCE 19.0
#define TANK_MAX_WATER_LEVEL_DISTANCE 4.0
#define TANK_VOLUME 3000
#define TANK_WAIT_FOR_READ_DISTANCE 100

#define CAUDALIMETER_BUFFER_SIZE 60
#define CAUDALIMETER_SAMPLE_RATE 1000

#define WAIT_FOR_PUBLISH_LOOP 1000
#define WAIT_FOR_PUBLISH_START 5000

// TODO: tank controller?
Relay pumpRelay(PUMP_RELAY_PIN);
HCSR04 waterDistance(WATER_DISTANCE_TRIGGER_PIN, WATER_DISTANCE_ECHO_PIN);
Tank tank(TANK_MIN_WATER_LEVEL_DISTANCE, TANK_MAX_WATER_LEVEL_DISTANCE, TANK_VOLUME);
Wait waitforReadDistance(TANK_WAIT_FOR_READ_DISTANCE);

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

void loop() {

  if (waitforReadDistance.done()) {
    // TODO this returns wrong distance some times and turn off pump at mid level
    tank.setWaterLevelDistance(waterDistance.getDistanceInCm());

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

  }

  caudalimeterSampler.sample(caudalimeter.getTickCount());

  if (waitforPublish.done()) {
    noInterrupts();

    publishDebug(tank, caudalimeter, caudalimeterSampler);

    interrupts();
  }

}

void publishDebug(Tank tank, Caudalimeter caudalimeter, CaudalimeterSampler caudalimeterSampler) {
  Serial.print(tank.getWaterLevelDistance());
  Serial.print(", ");

  Serial.print(tank.getEmptiedTimeSpanInSeconds());
  Serial.print(", ");

  Serial.print(tank.getEmptiedFlowInMlPerMinute());
  Serial.print(", ");


  Serial.print(caudalimeter.getTickCount());
  Serial.print(", ");

  // 3000 ml -> 949 tick count
  const float k = 3000.0 / 949.0;
  const unsigned int volumeBasedOnTickCount = (int)round(caudalimeter.getTickCount() * k);
  Serial.print(volumeBasedOnTickCount);
  Serial.print(", ");

  const unsigned int freq = caudalimeterSampler.getFrequency();
  Serial.print(caudalimeterSampler.getFrequency());
  Serial.print(", ");

  const float flow = freq * k;
  Serial.print(flow);
  Serial.print(", ");

  // Serial.print("reference flow (ml/minute): ");
  // Serial.print(tank.getEmptiedFlowInMlPerMinute());

  // Serial.print(" caudalimeter frequency (cycles/minute): ");
  // Serial.print(caudalimeterSampler.getFrequency());

  Serial.println();
}
