#include "scheduler.h"
#include "comms.h"
#include "protocol.h"

void comms_task();
void telemetry_task();
void command_task();

task_t tasks[] = {
    {comms_task, 10, 0},
    {telemetry_task, 1000, 0},
    {command_task, 1000, 0}
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

void telemetry_task(){

    uint8_t buffer[MAX_PACKET_SIZE];

    int len = protocol_build_telemetry(buffer);

    comms_publish_binary("rover/telemetry", buffer, len);

}

void command_task(){

    uint8_t buffer[MAX_PACKET_SIZE];

    if(comms_receive(buffer, MAX_PACKET_SIZE))
    {
        protocol_parse_command(buffer, MAX_PACKET_SIZE);
    }

}