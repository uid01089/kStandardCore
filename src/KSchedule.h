#ifndef KSCHEDULE_h
#define KSCHEDULE_h

#include <functional>

#include "ScheduleEntry.h"
#define MAX_TABLE_ENTRIES 200

class KSchedule
{
private:

    ScheduleEntry scheduleTable[MAX_TABLE_ENTRIES];
    unsigned int nrFreeElements = MAX_TABLE_ENTRIES;

public:
    KSchedule();
    ~KSchedule();
    void setup();
    void loop();
    unsigned int getNumberOfFreeElements();
    
    /**
    e.g.
    kSchedule.schedule(std::bind(clcWaterMeasurement1_500ms), 5000); or
    kschedule->schedule(std::bind(&Klasse::callback, this), 500); or
    kSchedule.schedule(clcWaterMeasurement2_500ms, 5000);
    */
    void schedule(std::function<void(void)> fct, unsigned long timePeriode);
};

#endif