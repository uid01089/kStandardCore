#ifndef KSCHEDULE_h
#define KSCHEDULE_h

#include <list>
#include <functional>

#include "ScheduleEntry.h"

class KSchedule
{
private:
    std::list<ScheduleEntry *> scheduleList;

public:
    KSchedule();
    ~KSchedule();
    void setup();
    void loop();
    /**
    e.g.
    kSchedule.schedule(std::bind(clcWaterMeasurement1_500ms), 5000); or
    kschedule->schedule(std::bind(&Klasse::callback, this), 500); or
    kSchedule.schedule(clcWaterMeasurement2_500ms, 5000);
    */
    void schedule(std::function<void(void)> fct, unsigned long timePeriode);
};

#endif