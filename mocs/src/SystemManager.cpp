#include "SystemManager.h"

SystemManager::SystemManager(
    Button *mB,
    Button *rB,
    LED *sL,
    LED *dL)
    : modeButton(mB), resetButton(rB), stateLED(sL), diagLED(dL), state(SystemState::BOOT), startTime(0), prevState(SystemState::BOOT), stateChanged(false)
{
}

void SystemManager::begin()
{
    modeButton->begin();
    resetButton->begin();
    stateLED->begin();
    diagLED->begin();
}

void SystemManager::update()
{
    now = millis();
    stateChanged = false;

    modeButton->update();
    resetButton->update();
    stateLED->update();
    diagLED->update();

    if (state == SystemState::BOOT)
    {
        if (now - startTime >= 5000)
        {
            setState(SystemState::ACTIVE);
        }
    }

    if (state == SystemState::RECOVERY)
    {
        if (now - startTime >= 2000)
        {
            setState(SystemState::IDLE);
        }
    }

    if (state != prevState)
    {
        onEnterState(state);
        prevState = state;
    }

    updateModeResetButton();
    if (stateChanged)
        return;

    updateModeButton();
    if (stateChanged)
        return;

    updateResetButton();
}

void SystemManager::setState(SystemState newState)
{
    if (state != newState)
    {
        state = newState;
        stateChanged = true;
    }
}

void SystemManager::onEnterState(SystemState state)
{
    startTime = millis();
    switch (state)
    {
    case SystemState::BOOT:
        stateLED->setDuration(1000);
        stateLED->setShouldBlink(true);
        diagLED->setShouldBlink(false);
        diagLED->setState(false);
        break;
    case SystemState::IDLE:
        stateLED->setShouldBlink(false);
        stateLED->setState(false);
        diagLED->setDuration(1000);
        diagLED->setShouldBlink(true);
        break;
    case SystemState::ACTIVE:
        stateLED->setShouldBlink(false);
        stateLED->setState(true);
        diagLED->setShouldBlink(false);
        diagLED->setState(false);
        break;
    case SystemState::ERROR:
        stateLED->setShouldBlink(true);
        stateLED->setDuration(200);
        diagLED->setShouldBlink(true);
        diagLED->setDuration(200);
        break;
    case SystemState::RECOVERY:
        stateLED->setShouldBlink(false);
        stateLED->setState(false);
        diagLED->setShouldBlink(false);
        diagLED->setState(true);
        break;
    default:
        Serial.println("Unknown State");
        break;
    }
}

void SystemManager::updateModeButton()
{
    if (modeButton->isPressed())
    {
        if (state == SystemState::ACTIVE)
        {
            setState(SystemState::IDLE);
        }
        else if (state == SystemState::IDLE)
        {
            setState(SystemState::ACTIVE);
        }
    }
}

void SystemManager::updateResetButton()
{
    if (resetButton->isPressed())
    {
        if (state == SystemState::ERROR)
        {
            setState(SystemState::RECOVERY);
        }
    }
}

void SystemManager::updateModeResetButton()
{
    if (modeButton->isPressed() && resetButton->isPressed())
    {
        if (state == SystemState::ACTIVE || state == SystemState::IDLE)
        {
            setState(SystemState::ERROR);
        }
    }
}