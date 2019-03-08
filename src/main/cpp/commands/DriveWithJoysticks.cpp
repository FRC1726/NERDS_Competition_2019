/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoysticks.h"
#include "Robot.h"
#include "RobotMap.h"
#include <cmath>

DriveWithJoysticks::DriveWithJoysticks() {
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

  speed = applyDeadZone(speed, Robot::loader.getConfig(JOYSTICK_DRIVE_DEADZONE));
  turn = applyDeadZone(turn, Robot::loader.getConfig(JOYSTICK_DRIVE_DEADZONE));

  speed = driveProfile(speed, Robot::loader.getConfig(JOYSTICK_DRIVE_MAX), Robot::loader.getConfig(JOYSTICK_DRIVE_MIN));
  turn = driveProfile(turn, Robot::loader.getConfig(JOYSTICK_TURN_MAX), Robot::loader.getConfig(JOYSTICK_TURN_MIN));

  bool reverse = Robot::loader.getConfig(JOYSTICK_REVERSE_FORWARD);
  if(reverse){
    speed = -speed;
  }

  double angle1 = Robot::loader.getConfig(CAMERA_ANGLE_1);
  if(angle1 == Robot::cameraswivel.GetServoAngle()){
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

double DriveWithJoysticks::applyDeadZone(double input, double deadzone){
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

double DriveWithJoysticks::driveProfile(double input, double max, double min){
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