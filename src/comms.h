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
bool comms_receive(char* topic_buffer, char* payload_buffer, int max_len);