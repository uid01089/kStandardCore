#include "KMqtt.h"

KMqtt::KMqtt()
{
}

KMqtt::~KMqtt()
{
}
void KMqtt::setup(WiFiClient &espClient, String &mqttServer, const uint16_t port, String &id)
{
    pubsubclient.setClient(espClient);
    pubsubclient.setServer(mqttServer.c_str(), port);
    while (!pubsubclient.connected())
    {
        pubsubclient.connect(id.c_str());
        delay(100);
    }

    pubsubclient.setCallback(std::bind(&KMqtt::mqttCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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
