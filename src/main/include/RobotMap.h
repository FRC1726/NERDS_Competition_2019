/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//Elevator
constexpr int ELEVATOR_CAN_MOTOR = 2;
constexpr int ELEVATOR_CAN_PID_ID = 1;
constexpr int ELEVATOR_TIMEOUT = 10;
constexpr double ELEVATOR_FORWARD_SENSOR_LIMIT = 28;
constexpr double ELEVATOR_REVERSE_SENSOR_LIMIT = 0;

//drivetrain
constexpr int DRIVE_FRONT_LEFT = 3;
constexpr int DRIVE_BACK_LEFT = 4;
constexpr int DRIVE_FRONT_RIGHT = 5;
constexpr int DRIVE_BACK_RIGHT = 6;
constexpr int DRIVE_TIMEOUT = 10;

//encoders
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
constexpr int AXIS_RIGHT_TRIGGER = 2;
constexpr int AXIS_LEFT_TRIGGER = 3;

constexpr int DPAD_UP = 0;
constexpr int DPAD_RIGHT = 1;
constexpr int DPAD_DOWN = 2;
constexpr int DPAD_LEFT = 3;

//buttons
constexpr int BUTTON_A = 1;
constexpr int BUTTON_B = 2;
constexpr int BUTTON_X = 3;
constexpr int BUTTON_Y = 4;
constexpr int BUTTON_BUMPER_LEFT = 5;
constexpr int BUTTON_BUMPER_RIGHT = 6;

//solenoids
constexpr int EXTENDER_A = 0;
constexpr int EXTENDER_B = 1;
constexpr int LAUNCHER_A = 2;
constexpr int LAUNCHER_B = 3;
constexpr int GRABBER = 4;

//Lift
constexpr int LIFT_REVERSE_LIMIT_SWITCH = 4;
constexpr int LIFT_MOTOR = 0;
