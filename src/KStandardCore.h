#ifndef KSTANDARD_CORE_h
#define KSTANDARD_CORE_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <KMqtt.h>
#include <KSchedule.h>
#include <KSystem.h>
#include <MyNTPClient.h>

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
    MyNTPClient *getNTPClient();
    String& getHostname();

private:
    WiFiClient espClient;
    WiFiUDP ntpUDP;
    MyNTPClient timeClient;
    KMqtt kmqtt;
    KSchedule kschedule;
    KSystem ksystem;
    String hostname;

    void setupWiFi(String hostname, String ssid, String password);
};

#endif