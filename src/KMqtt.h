#ifndef KMQTT_H
#define KMQTT_H

#include <list>
#include <functional>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "Arduino.h"
#include "CallbackEntry.h"

class KMqtt
{
private:
    std::list<CallbackEntry *> callbackList;
    void mqttCallback(char *topic, uint8_t *payload, unsigned int length);
    static String payloadToString(byte *payload, unsigned int length);
    PubSubClient pubsubclient;

public:
    KMqtt();
    ~KMqtt();
    void setup(WiFiClient &espClient, String mqttServer, const uint16_t port, String id);
    void loop();
    void regCallBack(String topic, std::function<void(String)> fct);
    void publish(String topic, String payload);
};

#endif