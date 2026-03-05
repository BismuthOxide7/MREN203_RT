#include <Arduino.h>
#include "comms.h"
#include "scheduler.h"

void setup() {

    Serial.begin(115200);
    while(!Serial);

    if(!init_comms()) {
        Serial.println("WiFi module failed!");
        while(true);
    }

    Serial.println("Connected to WiFi");
}

void loop() {

    scheduler_run();

}