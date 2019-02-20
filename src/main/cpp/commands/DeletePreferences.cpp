/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeletePreferences.h"

#include "Robot.h"
#include "config.h"
#include <string>
#include <frc/DriverStation.h>

DeletePreferences::DeletePreferences() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void DeletePreferences::Initialize() {
  std::string file = Robot::loader.getChosenFile();
  if(file == "New"){
    frc::DriverStation::ReportError("Please Select a file to delete");
  } else{
    Robot::loader.deleteConfigFile(file);
  }
}

// Called repeatedly when this Command is scheduled to run
void DeletePreferences::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool DeletePreferences::IsFinished() { 
  return true; 
}

// Called once after isFinished returns true
void DeletePreferences::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeletePreferences::Interrupted() {}
