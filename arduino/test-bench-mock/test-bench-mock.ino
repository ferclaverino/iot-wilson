#include "src/gateways/MetricsGateway.h"
#include "src/time/Wait.h"
#include "src/domain/TicksFrequency.h"

// Domiain setup
#define MIN_FREQUENCY 5
#define MAX_FREQUENCY 10

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
int minPulseCount = MIN_FREQUENCY * (WAIT_FOR_PUBLISH_LOOP / 1000);
int maxPulseCount = MAX_FREQUENCY * (WAIT_FOR_PUBLISH_LOOP / 1000);

void loop() {

  if (waitforPublish.done()) {
    long pulseCount = random(minPulseCount, maxPulseCount);
    // metricsGateway.publishPulseCount(pulseCount);

    totalTicksCounts += pulseCount;
    unsigned int timeSpan = waitforPublish.getDoneTimeSpanInMillis();
    float frequency = ticksFrequency.getFrequencyInHz(totalTicksCounts, timeSpan);

    metricsGateway.publishFrequency(frequency, timeSpan);
  }
}
