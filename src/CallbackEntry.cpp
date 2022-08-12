#include "CallbackEntry.h"

CallbackEntry::CallbackEntry(String topic, std::function<void(String)> fct)
{
    this->fct = fct;
    this->topic = topic;
}
CallbackEntry::~CallbackEntry()
{
}

String CallbackEntry::getTopic()
{
    return topic;
}
std::function<void(String)> CallbackEntry::getFct()
{
    return fct;
}
