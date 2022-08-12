#ifndef CALLBACK_ENTRY_h
#define CALLBACK_ENTRY_h

#include <functional>
#include <Arduino.h>

class CallbackEntry
{

public:
    CallbackEntry(String topic, std::function<void(String)> fct);
    ~CallbackEntry();
    String getTopic();
    std::function<void(String)> getFct();

private:
    String topic;
    std::function<void(String)> fct;
};

#endif