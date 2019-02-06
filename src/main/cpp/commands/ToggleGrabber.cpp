/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleGrabber.h"

#include "Robot.h"

ToggleGrabber::ToggleGrabber() : frc::Command("Toggle Grabber") {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::elevator);
}

// Called just before this Command runs the first time
void ToggleGrabber::Initialize() {
  Robot::elevator.setGrabber(!Robot::elevator.getGrabber());
}

// Called repeatedly when this Command is scheduled to run
void ToggleGrabber::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleGrabber::IsFinished() { 
  return true;
}

// Called once after isFinished returns true
void ToggleGrabber::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleGrabber::Interrupted() {

}
