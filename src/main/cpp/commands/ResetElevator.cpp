/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ResetElevator.h"
#include "Robot.h"

ResetElevator::ResetElevator() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::elevator);
}

// Called just before this Command runs the first time
void ResetElevator::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ResetElevator::Execute() {
  Robot::elevator.runMotor(-1);
}

// Make this return true when this Command no longer needs to run execute()
bool ResetElevator::IsFinished() 
{
  return Robot::elevator.getLimitSwitch(); 
}

// Called once after isFinished returns true
void ResetElevator::End() {
  Robot::elevator.runMotor(0);
  Robot::elevator.setElevatorSetPoint(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetElevator::Interrupted() {
  Robot::elevator.runMotor(0);
  Robot::elevator.setElevatorSetPoint(0);
}
