/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleElevator.h"
#include "Robot.h"

ToggleElevator::ToggleElevator() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::lift);
}

// Called just before this Command runs the first time
void ToggleElevator::Initialize() {
 Robot::lift.setElevator(!Robot::lift.getElevator());
}

// Called repeatedly when this Command is scheduled to run
void ToggleElevator::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleElevator::IsFinished() { 
  return true;
}

// Called once after isFinished returns true
void ToggleElevator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleElevator::Interrupted() {

}
