/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunIntake.h"
#include "Robot.h"
#include "RobotMap.h"

RunIntake::RunIntake() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::elevator);
}

// Called just before this Command runs the first time
void RunIntake::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RunIntake::Execute() {
  double forward = Robot::oi.getAxis(AXIS_RIGHT_TRIGGER);
  double backward = Robot::oi.getAxis(AXIS_LEFT_TRIGGER);

  double speed = forward - backward;

  Robot::elevator.runMotor(speed);
}

// Make this return true when this Command no longer needs to run execute()
bool RunIntake::IsFinished() { 
  return false;
}

// Called once after isFinished returns true
void RunIntake::End() {
  Robot::elevator.runMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunIntake::Interrupted() {
  Robot::elevator.runMotor(0);
}
