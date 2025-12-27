#pragma once

enum class SystemState
{
    BOOT,
    IDLE,
    ACTIVE,
    ERROR,
    RECOVERY
};

inline const char *systemStateToString(SystemState state)
{
    switch (state)
    {
    case SystemState::BOOT:
        return "BOOTING";
        break;
    case SystemState::ACTIVE:
        return "ACTIVATED";
        break;
    case SystemState::ERROR:
        return "ERROR";
        break;
    case SystemState::IDLE:
        return "IDLE";
        break;
    case SystemState::RECOVERY:
        return "RECOVERYING";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}