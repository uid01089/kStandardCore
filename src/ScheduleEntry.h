#ifndef SCHEDULE_ENTRY_h
#define SCHEDULE_ENTRY_h

#include <functional>

class ScheduleEntry
{

public:
    ScheduleEntry(unsigned long startTime, unsigned long duration, std::function<void(void)> fct);
    ScheduleEntry();

    ~ScheduleEntry();
    unsigned long getStartTime();
    unsigned long getDuration();
    std::function<void(void)> getFct();
    bool isValid();
    void makeInValid();
    void makeValid(unsigned long startTime, unsigned long duration, std::function<void(void)> fct);

private:
    unsigned long startTime;
    unsigned long duration;
    std::function<void(void)> fct;
};

#endif
