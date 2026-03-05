#include "protocol.h"
#include "comms.h"
#include <string.h>

extern float linear_velocity;
extern float angular_velocity;
extern float battery_voltage;
extern uint8_t fault_flags;
extern rover_state_t rover_state;

int protocol_build_telemetry(uint8_t* buffer)
{
    telemetry_packet_t pkt;

    pkt.packet_id = TEL_PACKET_ID;
    pkt.state = rover_state;

    pkt.v = linear_velocity;
    pkt.w = angular_velocity;

    pkt.battery = battery_voltage;

    pkt.fault = fault_flags;

    memcpy(buffer, &pkt, sizeof(pkt));

    return sizeof(pkt);
}