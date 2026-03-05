#include "comms.h"

const char  ssid[] = "Wire";
const char  password[] = "12345678";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

char broker[] = "test.mosquitto.org";
#define port 1883
int status = WL_IDLE_STATUS;


bool init_comms(){
     if (WiFi.status() == WL_NO_MODULE) {
        return 0;
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
    mqttClient.connect(broker, port);
    mqttClient.subscribe("rover/cmd"); //TODO: SETUP SUBS
    return 1;
}

void comms_poll() {

    if (!mqttClient.connected()) {
        mqttClient.connect(broker, port);
    }

    mqttClient.poll();
}

bool comms_receive(uint8_t* buffer, int max_len)
{

    int messageSize = mqttClient.parseMessage();

    if(messageSize <= 0)
        return false;

    int i = 0;

    while(mqttClient.available() && i < max_len)
    {
        buffer[i++] = mqttClient.read();
    }

    return true;
}

bool comms_publish(const char* topic, const char* msg){
    mqttClient.beginMessage(topic);
    mqttClient.print(msg);
    mqttClient.endMessage();
    return true;
}

bool comms_publish_binary(const char* topic, uint8_t* data, int len)
{

    if(!mqttClient.connected())
        return false;

    mqttClient.beginMessage(topic);

    mqttClient.write(data, len);

    mqttClient.endMessage();

    return true;
}