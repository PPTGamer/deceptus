#pragma once

#include "joystick/gamecontrollerinfo.h"


class GameControllerData
{
public:

    static GameControllerData& getInstance();

    const GameControllerInfo& getJoystickInfo() const;

    void setJoystickInfo(const GameControllerInfo &joystickInfo);
    bool isControllerUsed() const;


private:

    GameControllerData() = default;

    static GameControllerData sInstance;

    GameControllerInfo mJoystickInfo;
};

