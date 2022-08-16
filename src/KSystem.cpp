#include <KSystem.h>

KSystem::KSystem() {}
KSystem::~KSystem() {}
void KSystem::setup(String hostname, KMqtt *kmqtt, KSchedule *kscheduler, MyNTPClient *timeClient)
{
    this->hostname = hostname;
    this->kmqtt = kmqtt;
    this->kscheduler = kscheduler;

    timeClient->update();
    this->startTime = timeClient->getTimeString();

    Serial.println("System started on " + startTime);

    // https://techoverflow.net/2021/11/09/minimal-platformio-esp8266-arduinoota-example/
    ArduinoOTA.begin();

    kmqtt->regCallBack("/" + hostname + "/system/request/startime", std::bind(&KSystem::mqttStartTime, this, std::placeholders::_1));
    kmqtt->regCallBack("/" + hostname + "/system/request/ip", std::bind(&KSystem::mqttIpAddr, this, std::placeholders::_1));
    kmqtt->regCallBack("/" + hostname + "/system/request/rssi", std::bind(&KSystem::mqttRSSI, this, std::placeholders::_1));
    kmqtt->regCallBack("/" + hostname + "/system/request/reset", std::bind(&KSystem::mqttReset, this, std::placeholders::_1));
    kmqtt->regCallBack("/" + hostname + "/system/request/kschedulefreeelements", std::bind(&KSystem::mqttKScheduleFreeElements, this, std::placeholders::_1));
    kmqtt->regCallBack("/" + hostname + "/system/request/espInfos", std::bind(&KSystem::mqttEspInfos, this, std::placeholders::_1));
}
void KSystem::loop()
{
    ArduinoOTA.handle();
}

void KSystem::mqttStartTime(String value)
{
    kmqtt->publish("/" + hostname + "/system/result/startime", startTime);
}

void KSystem::mqttIpAddr(String value)
{
    kmqtt->publish("/" + hostname + "/system/result/ip", WiFi.localIP().toString());
}

void KSystem::mqttRSSI(String value)
{
    kmqtt->publish("/" + hostname + "/system/result/rssi", String(WiFi.RSSI()).c_str());
}

void KSystem::mqttReset(String value)
{
    ESP.reset();
}

void KSystem::mqttKScheduleFreeElements(String value)
{
    kmqtt->publish("/" + hostname + "/system/result/kschedulefreeelements", String(kscheduler->getNumberOfFreeElements()).c_str());
}

void KSystem::mqttEspInfos(String value)
{
    kmqtt->publish("/" + hostname + "/system/result/ESP/FreeContStack", String(ESP.getFreeContStack()).c_str());
    kmqtt->publish("/" + hostname + "/system/result/ESP/FreeHeap", String(ESP.getFreeHeap()).c_str());
    kmqtt->publish("/" + hostname + "/system/result/ESP/HeapFragmentation", String(ESP.getHeapFragmentation()).c_str());
}