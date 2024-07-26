#include "src/gateways/MetricsGateway.h"
#include "src/time/Wait.h"
#include "src/domain/TicksFrequency.h"

// Waiters setup
#define WAIT_FOR_PUBLISH_LOOP 1000
#define WAIT_FOR_PUBLISH_START 5000

// Domain
TicksFrequency ticksFrequency;

// Waiters
Wait waitforPublish(WAIT_FOR_PUBLISH_LOOP, WAIT_FOR_PUBLISH_START);

// Gateways
MetricsGateway metricsGateway(Serial);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {

  if (waitforPublish.done()) {

    long pulseCount = random(5, 25);
    // metricsGateway.publishPulseCount(pulseCount);

    unsigned int timeSpan = waitforPublish.getDoneTimeSpanInMillis();
    float frequency = ticksFrequency.getFrequencyInHz(pulseCount, timeSpan);

    metricsGateway.publishFrequency(frequency, timeSpan);
  }
}
