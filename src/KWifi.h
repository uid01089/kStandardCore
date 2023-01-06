#ifndef KWIFI_H
#define KWIFI_H

#if defined(ESP32)
#include <WiFi.h>
#else 
#include <ESP8266WiFi.h>
#endif
#include <KSchedule.h>

typedef enum {
    KWIFI_NOT_CONNECTED       = 0,   // for compatibility with WiFi Shield library
    KWIFI_CONNECTING          = 1,
    KWIFI_CONNECTED           = 2,
    KWIFI_RESTART             = 4
} KWifiStatus;

class KWifi
{
private:
    KSchedule *kscheduler;
    String hostname;
    String ssid; 
    String password;
    KWifiStatus status;
    uint16_t timeoutCtr;

    void wifi_100ms();
public:
    KWifi();
    ~KWifi();
    void setup(KSchedule *kscheduler, String hostname, String ssid, String password);
    void loop();
};

#endif