#include "src/actuators/Relay.h"
#include "src/domain/Tank.h"
#include "src/time/Wait.h"
#include "src/sensors/Caudalimeter.h"
#include "src/sensors/Button.h"
#include <math.h>

#define CAUDALIMETER_PIN 2
#define MAX_LEVEL_BUTTON_PIN 3
#define MIN_LEVEL_BUTTON_PIN 4
#define PUMP_RELAY_PIN 7

#define TANK_MIN_WATER_LEVEL_DISTANCE 19.0
#define TANK_MAX_WATER_LEVEL_DISTANCE 4.0
#define TANK_VOLUME 3000

#define BUTTON_DEBOUNCE_TIME 50

#define WAIT_FOR_PUBLISH_LOOP 1000
#define WAIT_FOR_PUBLISH_START 5000

Relay pumpRelay(PUMP_RELAY_PIN);
Tank tank(TANK_MIN_WATER_LEVEL_DISTANCE, TANK_MAX_WATER_LEVEL_DISTANCE, TANK_VOLUME);
Button maxLevelButton(MAX_LEVEL_BUTTON_PIN, BUTTON_DEBOUNCE_TIME);
Button minLevelButton(MIN_LEVEL_BUTTON_PIN, BUTTON_DEBOUNCE_TIME);

Caudalimeter caudalimeter(CAUDALIMETER_PIN);

Wait waitforDebug(WAIT_FOR_PUBLISH_LOOP);

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
  }

  if (minLevelButton.isToggle()) {
    tank.setWaterLevelOnMin();
    publishMetrics(tank, caudalimeter);
  }

  if (tank.isMinLevel()) {
    pumpRelay.on();
  }

  if (tank.isMaxLevel()) {
    pumpRelay.off();
  }

  // debug(tank, caudalimeter);
}

void publishMetrics(Tank tank, Caudalimeter caudalimeter) {
  Serial.print(tank.getEmptiedTimeSpanInSeconds());
  Serial.print(", ");

  Serial.print(caudalimeter.getTickCount());
  Serial.println();
}

void debug(Tank tank, Caudalimeter caudalimeter) {
  if (waitforDebug.done()) {
    // There is a serial and interrupts issue: https://forum.arduino.cc/t/nointerrupts-and-serial-write-issues/140133
    // but I don´t have it
    // noInterrupts();
    publishDebug(tank, caudalimeter);
    // interrupts();
  }
}

void publishDebug(Tank tank, Caudalimeter caudalimeter) {
  Serial.print(tank.getWaterLevelDistance());
  Serial.print(", ");

  Serial.print(tank.getEmptiedTimeSpanInSeconds());
  Serial.print(", ");

  Serial.print(caudalimeter.getTickCount());
  Serial.print(", ");

  Serial.println();
}
