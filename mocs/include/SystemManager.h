#pragma once

#include "utils/button.h"
#include "utils/led.h"
#include "SystemState.h"

class SystemManager
{
private:
    unsigned long now;
    unsigned long startTime;

    Button *modeButton;
    Button *resetButton;
    LED *stateLED;
    LED *diagLED;

    SystemState state;
    SystemState prevState;

    bool stateChanged;

public:
    void begin();
    SystemManager(
        Button *mB,
        Button *rB,
        LED *sL,
        LED *dL);

    void update();
    void onEnterState(SystemState state);

    void setState(SystemState state);
    void updateModeButton();
    void updateResetButton();
    void updateModeResetButton();
};