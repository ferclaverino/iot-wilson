#include "ArduinoJson-v7.1.0.h"
#include "Wait.h"

#define WAIT_FOR_PUBLISH_LOOP 1000
#define WAIT_FOR_PUBLISH_START 10000

Wait waitforPublish(WAIT_FOR_PUBLISH_LOOP, WAIT_FOR_PUBLISH_START);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {

  if (waitforPublish.done()) {
    long flow = random(1000, 3000);
    long turnsCount = random(0, 10);

    JsonDocument jsonMetric = createJsonMetric(flow, turnsCount);
    publishJsonMetric(jsonMetric);
  }
}

JsonDocument createJsonMetric(long flow, long turnsCount) {
  JsonDocument doc;
  doc["flow"] = flow;
  doc["turnsCount"] = turnsCount;
  return doc;
}

void publishJsonMetric(JsonDocument doc) {
  serializeJson(doc, Serial);
  Serial.println();
}
