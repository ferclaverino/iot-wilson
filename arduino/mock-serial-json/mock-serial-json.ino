#include "src/gateways/MetricsGateway.h"
#include "src/time/Wait.h"

#define WAIT_FOR_PUBLISH_LOOP 1000
#define WAIT_FOR_PUBLISH_START 5000

MetricsGateway metricsGateway(Serial);
Wait waitforPublish(WAIT_FOR_PUBLISH_LOOP, WAIT_FOR_PUBLISH_START);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {

  if (waitforPublish.done()) {
    long turnsCount = random(0, 10);
    metricsGateway.publish(turnsCount);
  }
}
