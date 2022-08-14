#ifndef KSYSTEM_H
#define KSYSTEM_H

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <KSchedule.h>
#include <KMqtt.h>
#include <NTPClient.h>

class KSystem
{
private:
    KMqtt *kmqtt;
    KSchedule *kscheduler;
    String hostname;
    String startTime;

    void mqttStartTime(String value);
    void mqttIpAddr(String value);
    void mqttRSSI(String value);

public:
    KSystem();
    ~KSystem();
    void setup(String hostname, KMqtt *kmqtt, KSchedule *kscheduler, NTPClient *timeClient);
    void loop();
};

#endif