#ifndef MetricsGateray_h
#define MetricsGateray_h

#include "Arduino.h";
#include "../serialization/ArduinoJson-v7.1.0.h";

class MetricsGateway {
public:
  MetricsGateway(Stream& port);
  void publish(const unsigned long pulseCount);

private:
  Stream& _port;

  const JsonDocument createJsonMetric(const unsigned long pulseCount);
  void publishJsonMetric(const JsonDocument doc);
};

#endif