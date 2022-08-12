#ifndef KSTANDARD_CORE_h
#define KSTANDARD_CORE_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <KMqtt.h>
#include <KSchedule.h>
#include <KSystem.h>
#include <NTPClient.h>

class KStandardCore
{

public:
    KStandardCore();
    ~KStandardCore();
    void setup(String hostname, String ssid, String password, String mqttServer, uint16_t mqttPort);
    void loop();
    KMqtt *getKMqtt();
    KSchedule *getKSchedule();
    WiFiClient *getWiFiClient();
    NTPClient *getNTPClient();

private:
    WiFiClient espClient;
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    KMqtt kmqtt;
    KSchedule kschedule;
    KSystem ksystem;

    void setupWiFi(String hostname, String ssid, String password);
};

#endif