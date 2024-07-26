#include "src/actuators/Relay.h"
#include "src/sensors/HCSR04.h"
#include "src/domain/Tank.h"
#include "src/time/Wait.h"
#include "src/sensors/Caudalimeter.h"
#include "src/gateways/MetricsGateway.h"
#include "src/domain/TicksFrequency.h"

// Pins setup
#define CAUDALIMETER_PIN 2
#define PUMP_RELAY_PIN 7
#define WATER_DISTANCE_TRIGGER_PIN 8
#define WATER_DISTANCE_ECHO_PIN 9

// Domiain setup
#define TANK_MIN_WATER_LEVEL_DISTANCE 19.0
#define TANK_MAX_WATER_LEVEL_DISTANCE 4.0
#define TANK_VOLUME 3000

// Waiters setup
#define TANK_WAIT_FOR_READ_DISTANCE 100
#define WAIT_FOR_DEBUG 1000
#define WAIT_FOR_PUBLISH_LOOP 5000
#define WAIT_FOR_PUBLISH_START 5000

// Sensors and actuators
Relay pumpRelay(PUMP_RELAY_PIN);
HCSR04 waterDistance(WATER_DISTANCE_TRIGGER_PIN, WATER_DISTANCE_ECHO_PIN);
Caudalimeter caudalimeter(CAUDALIMETER_PIN);

// Domain
Tank tank(TANK_MIN_WATER_LEVEL_DISTANCE, TANK_MAX_WATER_LEVEL_DISTANCE, TANK_VOLUME);
TicksFrequency ticksFrequency;

// Waiters
Wait waitforReadDistance(TANK_WAIT_FOR_READ_DISTANCE);
Wait waitforDebug(WAIT_FOR_DEBUG);
Wait waitforPublish(WAIT_FOR_PUBLISH_LOOP, WAIT_FOR_PUBLISH_START);

// Gateways
MetricsGateway metricsGateway(Serial);

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
    // TODO this returns wrong distances some times and turn off pump at mid level
    tank.setWaterLevelDistance(waterDistance.getDistanceInCm());

    if (tank.isMinLevel()) {
      if (!pumpRelay.isOn()) {
        publishPendingMetrics();
      }
      pumpRelay.on();
    }

    if (tank.isMaxLevel()) {
      if (pumpRelay.isOn()) {
        caudalimeter.reset();
        ticksFrequency.reset();
      }
      pumpRelay.off();
    }

  }

  if (tank.isLevelGoingDown()) {
    waitAndPublishMetrics();
  }

  // debug();

}

void waitAndPublishMetrics() {
  if (waitforPublish.done()) {
    unsigned int timeSpan = waitforPublish.getDoneTimeSpanInMillis();
    publishMetrics(timeSpan);
  }
}

void publishPendingMetrics() {
  unsigned int timeSpan = waitforPublish.getInProgressTimeSpanInMillis();
  publishMetrics(timeSpan);
}

void publishMetrics(unsigned int timeSpan) {
  // metricsGateway.publishPulseCount(caudalimeter.getTickCount());
  // caudalimeter.reset();

  float frequency = ticksFrequency.getFrequencyInHz(
    caudalimeter.getTickCount(),
    timeSpan
  );

  metricsGateway.publishFrequency(frequency, timeSpan);
}

void debug() {
  if (waitforDebug.done()) {
    // There is a serial and interrupts issue: https://forum.arduino.cc/t/nointerrupts-and-serial-write-issues/140133
    // but I don´t have it
    // noInterrupts();

    Serial.print(tank.getWaterLevelDistance());
    Serial.print(", ");

    Serial.print(tank.getEmptiedTimeSpanInSeconds());
    Serial.print(", ");

    Serial.print(caudalimeter.getTickCount());
    Serial.print(", ");

    Serial.print(ticksFrequency.getFrequencyInHz(
      caudalimeter.getTickCount(),
      waitforDebug.getDoneTimeSpanInMillis()
    ));
    Serial.print(", ");

    Serial.println();

    // interrupts();
  }
}
