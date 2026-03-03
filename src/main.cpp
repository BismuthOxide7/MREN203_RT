#include <Arduino.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

const char  ssid[] = "Wire";
const char  password[] = "12345678";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int port = 1883;
int status = WL_IDLE_STATUS;
unsigned long lastPublish = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  status = WiFi.begin(ssid, password);
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, password);

    // wait 5 seconds for connection:
    delay(5000);
  }
  Serial.println("Connected to WiFi");
  

  mqttClient.connect(broker, port);
}

void loop() {

    mqttClient.poll();   // IMPORTANT — must be called regularly

    if (millis() - lastPublish > 1000) {
        lastPublish = millis();
        Serial.println("Publishing to rover/telemetry");
        mqttClient.beginMessage("rover/telemetry");
        mqttClient.print("hello from rover");
        mqttClient.endMessage();
    }
}