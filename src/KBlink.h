#ifndef KBLINK_H
#define KBLINK_H

#include <Arduino.h>
#include <KSchedule.h>


class KBlink
{
private:
    KSchedule *kscheduler;
    uint16_t ontimeMs;
    uint16_t offtimeMs;

    void switchOn();
    void switchOff();
public:
    KBlink();
    ~KBlink();
    void setup(KSchedule *kscheduler, uint16_t ontimeMs, uint16_t offtimeMs);
    void loop();
};

#endif