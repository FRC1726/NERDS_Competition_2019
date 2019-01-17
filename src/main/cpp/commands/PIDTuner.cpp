/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PIDTuner.h"
#include "Robot.h"
#include "config.h"

PIDTuner::PIDTuner() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void PIDTuner::Initialize() {
  relaySpeed = Robot::loader.getConfig(AUTOTUNE_RELAY_SPEED);
  deadband = Robot::loader.getConfig(AUTOTUNE_TRIGGER_DEADBAND);
  Robot::drivetrain.resetGyro();
  Robot::drivetrain.arcadeDrive(0,relaySpeed);
  previousAngle = 0;
  potentialPeak = false;
}

// Called repeatedly when this Command is scheduled to run
void PIDTuner::Execute() {
  double angle = Robot::drivetrain.getAngle();
  double speed;
  if(angle > deadband){
    speed = -relaySpeed;
  }else if(angle < -deadband){
    speed = relaySpeed;
  }
  Robot::drivetrain.arcadeDrive(0,speed);

}

// Make this return true when this Command no longer needs to run execute()
bool PIDTuner::IsFinished() { return false; }

// Called once after isFinished returns true
void PIDTuner::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDTuner::Interrupted() {}

double PIDTuner::findPeak(double angle){
  if(previousAngle > angle && potentialPeak){
    potentialPeak = false;
    return angle;
  }else if(previousAngle < angle){
    potentialPeak = true;
  }else{
    potentialPeak = false;
  }

  return 360;
}
