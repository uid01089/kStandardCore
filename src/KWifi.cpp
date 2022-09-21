#include <KWifi.h>

#define TIME_TO_BE_CONNECTED_100MS 20

KWifi::KWifi()
{
    status = KWIFI_NOT_CONNECTED;
}
KWifi::~KWifi() {}

void KWifi::setup(KSchedule *kscheduler, String hostname, String ssid, String password)
{
    this->kscheduler = kscheduler;
    this->hostname = hostname;
    this->ssid = ssid;
    this->password = password;

    WiFi.mode(WIFI_STA);
    WiFi.hostname(hostname.c_str());
    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    status = KWIFI_CONNECTED;

    wifi_100ms();
}
void KWifi::loop() {}

void KWifi::wifi_100ms()
{

    if (WiFi.status() != WL_CONNECTED)
    {
        switch (status)
        {
        case KWIFI_CONNECTED:
            // It was connected, but connection get's lost

            WiFi.disconnect();
            WiFi.begin(ssid.c_str(), password.c_str());
            timeoutCtr = TIME_TO_BE_CONNECTED_100MS;
            status = KWIFI_CONNECTING;

            break;

        case KWIFI_CONNECTING:
            // Still connecting, just waiting
            if (timeoutCtr > 0)
            {
                timeoutCtr--;
            }
            else
            {
                // Timeout reached, do restart
                status = KWIFI_RESTART;
            }

            break;

        case KWIFI_RESTART:
            // Waiting time ended. Restart ESP
            Serial.println("Wifi Timeout reached, do restart");

            ESP.restart();
            break;

        default:
            // assume we are connected
            break;
        }
    }
    else
    {
        status = KWIFI_CONNECTED;
    }

    kscheduler->schedule(std::bind(&KWifi::wifi_100ms, this), 100);
}