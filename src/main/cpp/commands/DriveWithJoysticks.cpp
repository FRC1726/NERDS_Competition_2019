/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoysticks.h"
#include "Robot.h"
#include "RobotMap.h"

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
  double speed = Robot::oi.getAxis(AXIS_LEFT_X);
  double turn = Robot::oi.getAxis(AXIS_RIGHT_Y);
  
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
