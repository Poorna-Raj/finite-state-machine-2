#pragma once

#include <Arduino.h>

class Button
{
private:
    const uint8_t pin;
    bool state;
    bool previous;
    bool current;

public:
    void begin();
    Button(const uint8_t pin);
    void update();

    bool isPressed();
};