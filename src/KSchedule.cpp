#include <list>
#include <algorithm> // std::min
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

    for (int i = 0; i < MAX_TABLE_ENTRIES; i++)
    {
        ScheduleEntry *runningElement = &scheduleTable[i];
        if (runningElement->isValid())
        {
            // Valid element found in table, check it

            // https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover/12588#12588
            if (millis() - runningElement->getStartTime() > runningElement->getDuration())
            {
                // Call the function
                (runningElement->getFct())();

                // Store data to delete afterwards
                runningElement->makeInValid();
            }
        }
    }

    /*
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

    */
}

void KSchedule::schedule(std::function<void(void)> fct, unsigned long timePeriode)
{
    int ctrToFirstInvalidElement = 0;

    // Search fist element in table, which is invalide and free for use
    for (int i = 0; i < MAX_TABLE_ENTRIES; i++)
    {
        ScheduleEntry *runningElement = &scheduleTable[i];
        if (!runningElement->isValid())
        {
            runningElement->makeValid(millis(), timePeriode, fct);
            ctrToFirstInvalidElement = i;
            break;
        }
    }

    // go on searching invalide (free) table entries
    unsigned int freeElements = 0;
    for (int i = ctrToFirstInvalidElement; i < MAX_TABLE_ENTRIES; i++)
    {
        ScheduleEntry *runningElement = &scheduleTable[i];
        if (!runningElement->isValid())
        {
            freeElements++;
        }
    }

    nrFreeElements = std::min(nrFreeElements, freeElements);

    /*
    ScheduleEntry *scheduleEntry = new ScheduleEntry(millis(), timePeriode, fct);
    scheduleList.push_back(scheduleEntry);
    */
}

unsigned int KSchedule::getNumberOfFreeElements()
{

    return nrFreeElements;
}
