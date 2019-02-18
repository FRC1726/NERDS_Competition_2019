/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleSwivel.h"
#include "Robot.h"

#include "config.h"

ToggleSwivel::ToggleSwivel() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::cameraswivel);
}

// Called just before this Command runs the first time
void ToggleSwivel::Initialize() {
  double angle1 = Robot::loader.getConfig(CAMERA_ANGLE_1);
  double angle2 = Robot::loader.getConfig(CAMERA_ANGLE_2);

  if(Robot::cameraswivel.GetServoAngle() == angle1){
    Robot::cameraswivel.SetServoAngle(angle2);
  }else{
    Robot::cameraswivel.SetServoAngle(angle1);
  }
}

// Called repeatedly when this Command is scheduled to run
void ToggleSwivel::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleSwivel::IsFinished() {
 return true;
 }

// Called once after isFinished returns true
void ToggleSwivel::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleSwivel::Interrupted() {

}
