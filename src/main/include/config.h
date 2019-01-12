#pragma once

#include <string>


template <typename T>
struct ParameterKey {
    std::string key;
    T value;
};
//Joystick Preferences
const ParameterKey<double> JOYSTICK_DRIVE_MAX = {"Joystick/Drive/Max Speed", 1};
const ParameterKey<double> JOYSTICK_DRIVE_MIN = {"Joystick/Drive/Min Speed", 0.35};
const ParameterKey<double> JOYSTICK_DRIVE_DEADZONE = {"Joystick/Drive/Deadzone", 0.02};
const ParameterKey<double> JOYSTICK_DRIVE_QUICK_TURN = {"Joystick/Drive/Quickturn", 0.02};
//AutoTurn Preferences
const ParameterKey<double> AUTOTURN_RANGE_MAX = {"AutoTurn/Max Speed", 1};
const ParameterKey<double> AUTOTURN_RANGE_MIN = {"AutoTurn/Min Speed", -1};
const ParameterKey<double> AUTOTURN_PID_PROPORTIONAL = {"AutoTurn/PID/Proportional", 1};
const ParameterKey<double> AUTOTURN_PID_INTEGRAL = {"AutoTurn/PID/Integral Speed", 0};
const ParameterKey<double> AUTOTURN_PID_DERIVATIVE = {"AutoTurn/PID/Derivative", 0};

