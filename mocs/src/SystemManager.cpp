#include "SystemManager.h"

SystemManager::SystemManager(
    Button *mB,
    Button *rB,
    LED *sL,
    LED *dL)
    : startTime(0), modeButton(mB), resetButton(rB), stateLED(sL), diagLED(dL), state(SystemState::BOOT), prevState(SystemState::BOOT), stateChanged(false)
{
}

void SystemManager::begin()
{
    modeButton->begin();
    resetButton->begin();
    stateLED->begin();
    diagLED->begin();

    onEnterState(state);
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
    updateModeButton();
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
        Serial.println("BOOT");
        break;
    case SystemState::IDLE:
        stateLED->setShouldBlink(false);
        stateLED->setState(false);
        diagLED->setDuration(1000);
        diagLED->setShouldBlink(true);
        Serial.println("IDLE");
        break;
    case SystemState::ACTIVE:
        stateLED->setShouldBlink(false);
        stateLED->setState(true);
        diagLED->setShouldBlink(false);
        diagLED->setState(false);
        Serial.println("ACTIVE");
        break;
    case SystemState::ERROR:
        stateLED->setShouldBlink(true);
        stateLED->setDuration(200);
        diagLED->setShouldBlink(true);
        diagLED->setDuration(200);
        Serial.println("ERROR");
        break;
    case SystemState::RECOVERY:
        stateLED->setShouldBlink(false);
        stateLED->setState(false);
        diagLED->setShouldBlink(false);
        diagLED->setState(true);
        Serial.println("RECOVERY");
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
    if (digitalRead(modeButton->getPin()) && digitalRead(resetButton->getPin()))
    {
        if (state == SystemState::ACTIVE || state == SystemState::IDLE)
        {
            setState(SystemState::ERROR);

            modeButton->isPressed();
            resetButton->isPressed();
        }
    }
}