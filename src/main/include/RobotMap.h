/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//Lift
constexpr int LIFT_CAN_MOTOR = 2;
constexpr int LIFT_TIMEOUT = 10;
constexpr int LIFT_SOLENOID = 1;

//drivetrain
constexpr int DRIVE_FRONT_LEFT = 0;
constexpr int DRIVE_BACK_LEFT = 1;
constexpr int DRIVE_FRONT_RIGHT = 3;
constexpr int DRIVE_BACK_RIGHT = 2;

//encodews stuff owo
constexpr int ENCODER_LEFT_SELECT = 1;
constexpr int ENCODER_RIGHT_SELECT = 2;

constexpr int ENCODER_LEFT_A = 0;
constexpr int ENCODER_LEFT_B = 1;
constexpr int ENCODER_RIGHT_A = 2;
constexpr int ENCODER_RIGHT_B = 3;

constexpr double PULSES_PER_REVOLUTION = 360;
constexpr double GEARING_RATIO = 1;
constexpr double WHEEL_DIAMETER = 6;
constexpr double PI = 3.14159265358979323846;

//joysticks
constexpr int JOYSTICK_DRIVER = 0;
constexpr int AXIS_LEFT_X = 0;
constexpr int AXIS_LEFT_Y = 1;
constexpr int AXIS_RIGHT_X = 4;
constexpr int AXIS_RIGHT_Y = 5;
constexpr int AXIS_RIGHT_TRIGGER = 3;
constexpr int AXIS_LEFT_TRIGGER = 2;

//buttons
constexpr int BUTTON_A = 1;
constexpr int BUTTON_B = 2;
constexpr int BUTTON_X = 3;
constexpr int BUTTON_Y = 4;
constexpr int BUTTON_BUMPER_LEFT = 5;
constexpr int BUTTON_BUMPER_RIGHT = 6;
