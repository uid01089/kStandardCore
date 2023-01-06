#include <KBlink.h>

// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

#if defined(ESP32)
#define LED_PIN 2
#else
#define LED_PIN D4
#endif

KBlink::KBlink() {}
KBlink::~KBlink() {}
void KBlink::setup(KSchedule *kscheduler, uint16_t ontimeMs, uint16_t offtimeMs)
{
    this->kscheduler = kscheduler;
    this->ontimeMs = ontimeMs;
    this->offtimeMs = offtimeMs;

    pinMode(LED_PIN, OUTPUT);

    switchOn();
}
void KBlink::loop() {}

void KBlink::switchOn()
{
    digitalWrite(LED_PIN, LOW);
    kscheduler->schedule(std::bind(&KBlink::switchOff, this), ontimeMs);
}
void KBlink::switchOff()
{
    digitalWrite(LED_PIN, HIGH);
    kscheduler->schedule(std::bind(&KBlink::switchOn, this), offtimeMs);
}
