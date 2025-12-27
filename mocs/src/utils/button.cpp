#include "utils/button.h"

void Button::begin()
{
    pinMode(pin, INPUT);
}

Button::Button(const uint8_t pin)
    : pin(pin), state(false), previous(false), current(false) {}

void Button::update()
{
    current = digitalRead(pin);

    if (current && !previous)
    {
        state = true;
    }

    previous = current;
}

bool Button::isPressed()
{
    if (state)
    {
        state = false;
        return true;
    }
    return false;
}

uint8_t Button::getPin() const
{
    return pin;
}