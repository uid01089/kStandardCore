#include "KMqtt.h"

#define TIME_TO_BE_CONNECTED_100MS 20

KMqtt::KMqtt()
{
    status = KMQTT_NOT_CONNECTED;
}

KMqtt::~KMqtt()
{
}
void KMqtt::setup(KSchedule *kscheduler, WiFiClient &espClient, String &mqttServer, const uint16_t port, String &id)
{
    this->kscheduler = kscheduler;
    this->id = id;

    pubsubclient.setClient(espClient);
    pubsubclient.setServer(mqttServer.c_str(), port);
    while (!pubsubclient.connected())
    {
        pubsubclient.connect(id.c_str());
        delay(100);
    }

    pubsubclient.setCallback(std::bind(&KMqtt::mqttCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    status = KMQTT_CONNECTED;

    kmqtt_100ms();
}
void KMqtt::loop()
{
    pubsubclient.loop();
}

void KMqtt::regCallBack(String topic, std::function<void(String)> fct)
{
    CallbackEntry *scheduleEntry = new CallbackEntry(topic, fct);
    callbackList.push_back(scheduleEntry);
    pubsubclient.subscribe(topic.c_str());
}

void KMqtt::mqttCallback(char *topic, uint8_t *payload, unsigned int length)
{

    String topicAsString = String(topic);
    String payloadAsString = KMqtt::payloadToString(payload, length);

    for (CallbackEntry *entry : callbackList)
    {
        if (topicAsString == entry->getTopic())
        {
            // Call the function
            (entry->getFct())(payloadAsString);
        }
    }
}

void KMqtt::publish(String topic, String payload)
{
    pubsubclient.publish(topic.c_str(), payload.c_str());
}

String KMqtt::payloadToString(byte *payload, unsigned int length)
{
    char messageBuffer[length];             // somewhere to put the message
    memcpy(messageBuffer, payload, length); // copy in the payload
    messageBuffer[length] = '\0';
    return String(messageBuffer);
}

void KMqtt::kmqtt_100ms()
{
    if (!pubsubclient.connected())
    {
        switch (status)
        {
        case KMQTT_CONNECTED:

            // It was connected, but connection get's lost

            status = KMQTT_WAITING_NETWORK;
            // no break;

        case KMQTT_WAITING_NETWORK:

            if (WiFi.status() != WL_CONNECTED)
            {
                // No Wifi, wait till WiFi is available, then go on
            }
            else
            {
                // WiFi available, do mqtt connecting
                timeoutCtr = TIME_TO_BE_CONNECTED_100MS;
                pubsubclient.connect(id.c_str());
            }

            status = KMQTT_CONNECTING;

            break;

        case KMQTT_CONNECTING:
            // Still connecting, just waiting
            if (timeoutCtr > 0)
            {
                timeoutCtr--;
            }
            else
            {
                // Timeout reached, do restart
                Serial.println("MQTT Timeout reached, do restart");
                status = KMQTT_RESTART;
            }

            break;

        case KMQTT_RESTART:
            // Waiting time ended. Restart ESP
            ESP.restart();
            break;

        default:
            // assume we are connected
            break;
        }
    }
    else
    {
        if (status == KMQTT_CONNECTING)
        {
            // Status was connecting, but now successful connected
            pubsubclient.setCallback(std::bind(&KMqtt::mqttCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        }

        status = KMQTT_CONNECTED;
    }

    kscheduler->schedule(std::bind(&KMqtt::kmqtt_100ms, this), 100);
}
