#include "utils/button.h"

void Button::begin(){
    pinMode(pin,INPUT);
}

Button::Button(const uint8_t pin):
    pin(pin),
    current(false),
    previous(false),
    state(false){}

void Button::update(){
    current = digitalRead(pin);

    // TODO:: try with the condition of current != previous
    if(current && !previous){
        state = true;
    }

    previous = current;
}

bool Button::isPressed(){
    if(state){
        state = false;
        return true;
    }
    return false;
}