#pragma once

#include <stdint.h>

#define CMD_PACKET_ID  0xA1
#define TEL_PACKET_ID  0xB1

#define MAX_PACKET_SIZE 32

typedef enum
{
    CMD_STOP = 0,
    CMD_DRIVE = 1
} command_id_t;

typedef enum
{
    STATE_IDLE = 0,
    STATE_DRIVE = 1,
    STATE_FAULT = 2
} rover_state_t;

typedef struct
{
    uint8_t packet_id;
    uint8_t command;

    float v;
    float w;

} cmd_packet_t;


typedef struct
{
    uint8_t packet_id;

    uint8_t state;

    float v;
    float w;

    float battery;

    uint8_t fault;

} telemetry_packet_t;


int protocol_build_telemetry(uint8_t* buffer);

bool protocol_parse_command(uint8_t* buffer, int len);