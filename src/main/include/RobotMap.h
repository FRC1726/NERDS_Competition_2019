/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//drivetrain
constexpr int DRIVE_FRONT_LEFT = 0;
constexpr int DRIVE_FRONT_RIGHT = 1;
constexpr int DRIVE_BACK_LEFT = 2;
constexpr int DRIVE_BACK_RIGHT = 3;

//encodews stuff owo
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
constexpr int AXIS_RIGHT_X = 2;
constexpr int AXIS_RIGHT_Y = 3;
constexpr int AXIS_RIGHT_TRIGGER = 4;
constexpr int AXIS_LEFT_TRIGGER = 5;

//config
constexpr double DEAD_ZONE = .02;
constexpr double MIN = .35;
constexpr double MAX = 1;
constexpr double QUICK_TURN = .4;