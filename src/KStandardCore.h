#ifndef KSTANDARD_CORE_h
#define KSTANDARD_CORE_h


#if defined(ESP32)
#include <WiFi.h>
#else 
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include <KMqtt.h>
#include <KSchedule.h>
#include <KSystem.h>
#include <MyNTPClient.h>
#include <KWifi.h>

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
    KWifi kWifi;
    String hostname;

    
};

#endif