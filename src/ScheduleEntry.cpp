#include "ScheduleEntry.h"

ScheduleEntry::ScheduleEntry(unsigned long startTime, unsigned long duration, std::function<void(void)> fct)
{
    this->startTime = startTime;
    this->duration = duration;
    this->fct = fct;
}

ScheduleEntry::~ScheduleEntry()
{
}

unsigned long ScheduleEntry::getStartTime()
{
    return startTime;
}
unsigned long ScheduleEntry::getDuration()
{
    return duration;
}

std::function<void(void)> ScheduleEntry::getFct()
{
    return fct;
}
