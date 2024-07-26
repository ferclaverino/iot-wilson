#include "MetricsGateway.h"

MetricsGateway::MetricsGateway(Stream& port) : _port(port) {
}

void MetricsGateway::publishPulseCount(const unsigned long pulseCount) {
  JsonDocument jsonMetric;
  jsonMetric["pulseCount"] = pulseCount;
  publishJsonMetric(jsonMetric);
}

void MetricsGateway::publishFrequency(const float frequencyInHz, unsigned int timeSpanInMillis) {
  JsonDocument jsonMetric;
  jsonMetric["frequency"] = frequencyInHz;
  jsonMetric["timeSpan"] = timeSpanInMillis;
  publishJsonMetric(jsonMetric);
}

void MetricsGateway::publishJsonMetric(const JsonDocument jsonMetric) {
  serializeJson(jsonMetric, _port);
  _port.println();
}
