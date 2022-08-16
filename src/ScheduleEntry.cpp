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
ScheduleEntry::ScheduleEntry()
{
    this->startTime = 0;
    this->duration = 0;
    this->fct = NULL;
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

bool ScheduleEntry::isValid()
{
    return (this->fct != NULL);
}

void ScheduleEntry::makeInValid()
{
    this->startTime = 0;
    this->duration = 0;
    this->fct = NULL;
}

void ScheduleEntry::makeValid(unsigned long startTime, unsigned long duration, std::function<void(void)> fct)
{
    this->startTime = startTime;
    this->duration = duration;
    this->fct = fct;
}
