/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleExtender.h"

#include "Robot.h"

ToggleExtender::ToggleExtender() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::elevator);
}

// Called just before this Command runs the first time
void ToggleExtender::Initialize() {
  Robot::elevator.setExtender(!Robot::elevator.getExtender());
}

// Called repeatedly when this Command is scheduled to run
void ToggleExtender::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ToggleExtender::IsFinished() { return true; }

// Called once after isFinished returns true
void ToggleExtender::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleExtender::Interrupted() {}
