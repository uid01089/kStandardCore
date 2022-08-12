#include <list>
#include "KSchedule.h"
#include <Arduino.h>

KSchedule::KSchedule()
{
}

KSchedule::~KSchedule()
{
}

void KSchedule::setup()
{
}

void KSchedule::loop()
{
    std::list<ScheduleEntry *> deleteList;

    for (ScheduleEntry *entry : scheduleList)
    {

        // https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover/12588#12588
        if (millis() - entry->getStartTime() > entry->getDuration())
        {
            // Call the function
            (entry->getFct())();

            // Store data to delete afterwards
            deleteList.push_back(entry);
        }
    }

    for (auto const entry : deleteList)
    {
        scheduleList.remove(entry);
        delete entry;
    }
}

void KSchedule::schedule(std::function<void(void)> fct, unsigned long timePeriode)
{
    ScheduleEntry *scheduleEntry = new ScheduleEntry(millis(), timePeriode, fct);
    scheduleList.push_back(scheduleEntry);
}
