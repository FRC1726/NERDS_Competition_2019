/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunLift.h"

#include "config.h"
#include "Robot.h"
#include "RobotMap.h"

RunLift::RunLift() : frc::Command("Run Lift") {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::lift);
}

// Called just before this Command runs the first time
void RunLift::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RunLift::Execute() {
  double speed = Robot::loader.getConfig(LIFT_RUN_SPEED);
  if(Robot::oi.getDPad(DPAD_UP)){
    Robot::lift.run(speed);
  }else if(Robot::oi.getDPad(DPAD_DOWN)){
    Robot::lift.run(-speed);
  }else{
    Robot::lift.run(0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool RunLift::IsFinished() { return false; }

// Called once after isFinished returns true
void RunLift::End() {
  Robot::lift.run(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunLift::Interrupted() {
  Robot::lift.run(0);
}
