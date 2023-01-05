#include <KStandardCore.h>

#define utcOffsetInSeconds 3600

KStandardCore::KStandardCore() : timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds) {}
KStandardCore::~KStandardCore() {}

void KStandardCore::setup(String hostname, String ssid, String password, String mqttServer, uint16_t mqttPort)
{
    kschedule.setup();
    kWifi.setup(&kschedule, hostname, ssid, password);
    timeClient.begin();
    kmqtt.setup(&kschedule, espClient, mqttServer, mqttPort, hostname);
    ksystem.setup(hostname, &kmqtt, &kschedule, &timeClient);
    this->hostname = hostname;
}

void KStandardCore::loop()
{
    kWifi.loop();
    kmqtt.loop();
    kschedule.loop();
    ksystem.loop();
}

KMqtt *KStandardCore::getKMqtt()
{
    return &kmqtt;
}

KSchedule *KStandardCore::getKSchedule()
{
    return &kschedule;
}

WiFiClient *KStandardCore::getWiFiClient()
{
    return &espClient;
}

MyNTPClient *KStandardCore::getNTPClient()
{
    return &timeClient;
}

String &KStandardCore::getHostname()
{
    return hostname;
}
