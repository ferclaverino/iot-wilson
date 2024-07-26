#include "src/actuators/Relay.h"
#include "src/domain/Tank.h"
#include "src/time/Wait.h"
#include "src/sensors/Caudalimeter.h"
#include "src/sensors/Button.h"
#include "src/gateways/MetricsGateway.h"
#include "src/domain/TicksFrequency.h"

// Pins setup
#define CAUDALIMETER_PIN 2
#define MAX_LEVEL_BUTTON_PIN 3
#define MIN_LEVEL_BUTTON_PIN 4
#define PUMP_RELAY_PIN 7

// Sensors and actuators setup
#define BUTTON_DEBOUNCE_TIME 50

// Domiain setup
#define TANK_MIN_WATER_LEVEL_DISTANCE 19.0
#define TANK_MAX_WATER_LEVEL_DISTANCE 4.0
#define TANK_VOLUME 3000

// Waiters setup
#define WAIT_FOR_DEBUG 1000
#define WAIT_FOR_PUBLISH_LOOP 5000
#define WAIT_FOR_PUBLISH_START 5000

// Sensors and actuators
Button maxLevelButton(MAX_LEVEL_BUTTON_PIN, BUTTON_DEBOUNCE_TIME);
Button minLevelButton(MIN_LEVEL_BUTTON_PIN, BUTTON_DEBOUNCE_TIME);
Caudalimeter caudalimeter(CAUDALIMETER_PIN);
Relay pumpRelay(PUMP_RELAY_PIN);

// Domain
Tank tank(TANK_MIN_WATER_LEVEL_DISTANCE, TANK_MAX_WATER_LEVEL_DISTANCE, TANK_VOLUME);
TicksFrequency ticksFrequency;

// Waiters
Wait waitforDebug(WAIT_FOR_DEBUG);

// works for serial monitor
// Wait waitforPublish(WAIT_FOR_PUBLISH_LOOP);

// works for raspberry pi connection and nodered
// we need to wait 5 seconds until first publish
// to avoid nodered crash
Wait waitforPublish(WAIT_FOR_PUBLISH_LOOP, WAIT_FOR_PUBLISH_START);

// Gateways
MetricsGateway metricsGateway(Serial);

void caudalimeterTick() {
  caudalimeter.tick();
}

void setup() {
  Serial.begin(9600);
  pumpRelay.begin();
  caudalimeter.begin(caudalimeterTick);
  maxLevelButton.begin();
  minLevelButton.begin();
}

void loop() {

  if (maxLevelButton.isToggle()) {
    tank.setWaterLevelOnMax();
    caudalimeter.reset();
    ticksFrequency.reset();
  }

  if (minLevelButton.isToggle()) {
    tank.setWaterLevelOnMin();

    // When tank is at min level
    // could be there is some caudalimeter ticks between last published metrics and now
    // so we publish those pending metrics to avoid missing them
    publishPendingMetrics();
    // logTankEmptied();
  }

  if (tank.isMinLevel()) {
    pumpRelay.on();
  }

  if (tank.isMaxLevel()) {
    pumpRelay.off();
  }

  if (tank.isLevelGoingDown()) {
    waitAndPublishMetrics();
  }

  // debug();
}

void logTankEmptied() {
  Serial.print(tank.getEmptiedTimeSpanInSeconds());
  Serial.print(", ");

  Serial.print(caudalimeter.getTickCount());
  Serial.println();
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
    Serial.print("debug: ");

    Serial.print(waitforDebug.getDoneTimeSpanInMillis());
    Serial.print(", ");

    // There is a serial and interrupts issue: https://forum.arduino.cc/t/nointerrupts-and-serial-write-issues/140133
    // but I don´t have it
    // noInterrupts();

    // Serial.print(tank.isLevelGoingDown());
    // Serial.print(", ");

    // Serial.print(tank.getWaterLevelDistance());
    // Serial.print(", ");

    // Serial.print(tank.getEmptiedTimeSpanInSeconds());
    // Serial.print(", ");

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
