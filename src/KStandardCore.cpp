#include <KStandardCore.h>

#define utcOffsetInSeconds 3600

KStandardCore::KStandardCore() : timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds) {}
KStandardCore::~KStandardCore() {}

void KStandardCore::setup(String hostname, String ssid, String password, String mqttServer, uint16_t mqttPort)
{
    setupWiFi(hostname, ssid, password);
    timeClient.begin();
    kmqtt.setup(espClient, mqttServer, mqttPort, hostname);
    kschedule.setup();
    ksystem.setup(hostname, &kmqtt, &kschedule, &timeClient);
    this->hostname = hostname;
}

void KStandardCore::loop()
{
    kmqtt.loop();
    kschedule.loop();
    ksystem.loop();
}

void KStandardCore::setupWiFi(String hostname, String ssid, String password)
{
    WiFi.mode(WIFI_STA);
    WiFi.hostname(hostname.c_str());
    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }
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
