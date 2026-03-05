#pragma once
#include <Arduino.h>

typedef void (*task_func_t)(void);

typedef struct {
    task_func_t task;
    unsigned long period;
    unsigned long last_run;
} task_t;

void scheduler_init();
void scheduler_run();