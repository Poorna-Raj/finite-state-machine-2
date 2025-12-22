#pragma once

#include <Arduino.h>

class LED{
    private:
        const uint8_t pin;
        unsigned long startTime;
        unsigned long duration;

        bool shouldBlink;
        bool status;

    public:
        void begin();
        LED(const uint8_t pin,unsigned long duration);
        void update();

        void setState(bool state);
        void setShouldBlink(bool blink);
        void setDuration(unsigned long duration);
};