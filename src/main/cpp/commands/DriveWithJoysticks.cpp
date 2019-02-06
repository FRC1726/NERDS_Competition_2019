/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoysticks.h"

#include <cmath>

#include "Robot.h"
#include "RobotMap.h"

DriveWithJoysticks::DriveWithJoysticks() : frc::Command("Drive With Joysticks") {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void DriveWithJoysticks::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoysticks::Execute() {
  double speed = Robot::oi.getAxis(AXIS_LEFT_Y);
  double turn = Robot::oi.getAxis(AXIS_RIGHT_X);
  
  speed = apply_deadzone(speed, Robot::loader.getConfig(JOYSTICK_DRIVE_DEADZONE));
  turn = apply_deadzone(turn, Robot::loader.getConfig(JOYSTICK_DRIVE_DEADZONE));

  speed = drive_profile(speed, Robot::loader.getConfig(JOYSTICK_DRIVE_MAX), Robot::loader.getConfig(JOYSTICK_DRIVE_MIN));
  turn = drive_profile(turn, Robot::loader.getConfig(JOYSTICK_TURN_MAX), Robot::loader.getConfig(JOYSTICK_TURN_MIN));

  bool reverse = Robot::loader.getConfig(JOYSTICK_REVERSE_FORWARD);
  if(reverse){
    speed = -speed;
  }

  Robot::drivetrain.arcadeDrive(speed, turn);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoysticks::IsFinished() { 
  return false;
}

// Called once after isFinished returns true
void DriveWithJoysticks::End() {
  Robot::drivetrain.arcadeDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoysticks::Interrupted() {
  Robot::drivetrain.arcadeDrive(0, 0);
}

double DriveWithJoysticks::apply_deadzone(double input, double deadzone){
  double absolute = fabs(input);

  if(absolute < deadzone) {
   return 0;
  }

  double normalized = (absolute - deadzone)/(1 - deadzone);
  
  if(input < 0){
    return -normalized;
  }else{
    return normalized;
  }
}

double DriveWithJoysticks::drive_profile(double input, double max, double min){
  if(input == 0){
    return 0;
  }
  double absolute = fabs(input);

  double output = absolute * (max - min) + min;
  output *= output;

  if(input < 0){
    return -output;
  }else{
    return output;
  }
}