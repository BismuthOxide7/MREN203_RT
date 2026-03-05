#include "scheduler.h"
#include "comms.h"

void comms_task();
void telemetry_task();
void example_rcv_task();

task_t tasks[] = {
    {comms_task, 10, 0},
    {telemetry_task, 1000, 0},
    {example_rcv_task, 1000, 0}
};

const int num_tasks = sizeof(tasks) / sizeof(task_t);

void scheduler_run() {

    unsigned long now = millis();

    for(int i = 0; i < num_tasks; i++) {

        if(now - tasks[i].last_run >= tasks[i].period) {

            tasks[i].last_run = now;

            tasks[i].task();
        }
    }
}

void comms_task() {
    comms_poll();
}

void telemetry_task() {
    comms_publish("rover/telemetry","hello from rover");
}

void example_rcv_task(){
    char topic[64];
    char payload[128];

    if (comms_receive(topic, payload, sizeof(payload))) {

        Serial.print("RX Topic: ");
        Serial.println(topic);

        Serial.print("RX Payload: ");
        Serial.println(payload);
    }
}