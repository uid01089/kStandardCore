#ifndef SCHEDULE_ENTRY_h
#define SCHEDULE_ENTRY_h

#include <functional>

class ScheduleEntry
{

public:
    ScheduleEntry(unsigned long startTime, unsigned long duration, std::function<void(void)> fct);
    ~ScheduleEntry();
    unsigned long getStartTime();
    unsigned long getDuration();
    std::function<void(void)> getFct();

private:
    unsigned long startTime;
    unsigned long duration;
    std::function<void(void)> fct;
};

#endif
