#include "src/gateways/MetricsGateway.h"
#include "src/time/Wait.h"
#include "src/domain/TicksFrequency.h"

// Waiters setup
#define WAIT_FOR_PUBLISH_LOOP 5000
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

long totalTicksCounts = 0;

void loop() {

  if (waitforPublish.done()) {

    // Frequency will be between 1 (5/5) and 5 (25/5) hz
    long pulseCount = random(5, 25);
    // metricsGateway.publishPulseCount(pulseCount);

    totalTicksCounts += pulseCount;

    unsigned int timeSpan = waitforPublish.getDoneTimeSpanInMillis();
    float frequency = ticksFrequency.getFrequencyInHz(totalTicksCounts, timeSpan);

    metricsGateway.publishFrequency(frequency, timeSpan);
  }
}
