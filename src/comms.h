#pragma once

#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

extern WiFiClient wifiClient;
extern MqttClient mqttClient;

extern char broker[];
extern const int port;

bool init_comms();
void comms_poll();
bool comms_publish(const char* topic, const char* message);
bool comms_receive(uint8_t* buffer, int max_len);
bool comms_publish_binary(const char* topic, uint8_t* data, int len);