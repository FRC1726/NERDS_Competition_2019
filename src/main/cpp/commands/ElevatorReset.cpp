/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorReset.h"

#include "Robot.h"

ElevatorReset::ElevatorReset() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::elevator);
}

// Called just before this Command runs the first time
void ElevatorReset::Initialize() {
  Robot::elevator.runMotor(-1);
}

// Called repeatedly when this Command is scheduled to run
void ElevatorReset::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorReset::IsFinished() { 
  return Robot::elevator.GetReverseLimitSwitch();
}

// Called once after isFinished returns true
void ElevatorReset::End() {
  Robot::elevator.SetEncoderPosition(0);
  Robot::elevator.runMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorReset::Interrupted() {
  Robot::elevator.runMotor(0);
}
