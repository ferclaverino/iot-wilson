#include "MetricsGateway.h"

MetricsGateway::MetricsGateway(Stream& port) : _port(port) {
}

void MetricsGateway::publish(const unsigned long pulseCount) {
  JsonDocument jsonMetric = createJsonMetric(pulseCount);
  publishJsonMetric(jsonMetric);
}

const JsonDocument MetricsGateway::createJsonMetric(const unsigned long pulseCount) {
  JsonDocument jsonMetric;
  jsonMetric["pulseCount"] = pulseCount;
  return jsonMetric;
}

void MetricsGateway::publishJsonMetric(const JsonDocument jsonMetric) {
  serializeJson(jsonMetric, _port);
  _port.println();
}
