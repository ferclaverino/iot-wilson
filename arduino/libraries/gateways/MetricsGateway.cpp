#include "MetricsGateway.h"

MetricsGateway::MetricsGateway(Stream& port) : _port(port) {
}

void MetricsGateway::publish(const unsigned long turnsCount) {
  JsonDocument jsonMetric = createJsonMetric(turnsCount);
  publishJsonMetric(jsonMetric);
}

const JsonDocument MetricsGateway::createJsonMetric(const unsigned long turnsCount) {
  JsonDocument jsonMetric;
  jsonMetric["turnsCount"] = turnsCount;
  return jsonMetric;
}

void MetricsGateway::publishJsonMetric(const JsonDocument jsonMetric) {
  serializeJson(jsonMetric, _port);
  _port.println();
}
