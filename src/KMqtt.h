#ifndef KMQTT_H
#define KMQTT_H

#include <list>
#include <map>
#include <functional>
#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
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
    String hostname;
    std::map<String, String> onChangeDict;
    void resetPublishOnChangeBuffer(String value);

public:
    KMqtt();
    ~KMqtt();
    void setup(KSchedule *kscheduler, WiFiClient &espClient, String &mqttServer, const uint16_t port, String &hostname);
    void loop();
    void regCallBack(String topic, std::function<void(String)> fct);
    void publish(String topic, String payload);
    void publishOnChange(String topic, String payload);
    void forcedPublish(String topic, String payload);
};

#endif