#ifndef MetricsGateray_h
#define MetricsGateray_h

#include "Arduino.h";
#include "../serialization/ArduinoJson-v7.1.0.h";

class MetricsGateway {
public:
  MetricsGateway(Stream& port);
  void publish(const unsigned long turnsCount);

private:
  Stream& _port;

  const JsonDocument createJsonMetric(const unsigned long turnsCount);
  void publishJsonMetric(const JsonDocument doc);
};

#endif