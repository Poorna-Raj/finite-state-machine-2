#include "utils/led.h"

LED::LED(const uint8_t pin, unsigned long duration)
    : pin(pin), duration(duration), startTime(0), shouldBlink(false), status(false) {}

void LED::begin()
{
    pinMode(pin, OUTPUT);
    setState(false);
}

void LED::setDuration(unsigned long duration)
{
    this->duration = duration;
}

void LED::setShouldBlink(bool blink)
{
    if (shouldBlink != blink)
    {
        this->shouldBlink = blink;
        startTime = millis();
    }
}

void LED::setState(bool state)
{
    this->status = state;
    digitalWrite(pin, status);
}

void LED::update()
{
    unsigned long now = millis();
    if (shouldBlink)
    {
        if (now - startTime >= duration)
        {
            startTime = now;
            status = !status;
            digitalWrite(pin, status);
        }
    }
}