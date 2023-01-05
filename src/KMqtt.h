#ifndef KMQTT_H
#define KMQTT_H

#include <list>
#include <functional>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <KSchedule.h>

#include "Arduino.h"
#include "CallbackEntry.h"

typedef enum
{
    KMQTT_NOT_CONNECTED = 0,
    KMQTT_CONNECTING = 1,
    KMQTT_CONNECTED = 2,
    KMQTT_WAITING_NETWORK = 3,
    KMQTT_RESTART = 4
} KMqttStatus;

class KMqtt
{
private:
    KSchedule *kscheduler;
    KMqttStatus status;
    std::list<CallbackEntry *> callbackList;
    void mqttCallback(char *topic, uint8_t *payload, unsigned int length);
    static String payloadToString(byte *payload, unsigned int length);
    PubSubClient pubsubclient;
    void kmqtt_100ms();
    uint16_t timeoutCtr;
    String id;

public:
    KMqtt();
    ~KMqtt();
    void setup(KSchedule *kscheduler, WiFiClient &espClient, String &mqttServer, const uint16_t port, String &id);
    void loop();
    void regCallBack(String topic, std::function<void(String)> fct);
    void publish(String topic, String payload);
};

#endif