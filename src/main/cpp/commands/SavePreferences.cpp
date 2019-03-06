/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SavePreferences.h"

#include "Robot.h"
#include "config.h"

#include <frc/smartdashboard/SmartDashboard.h>

SavePreferences::SavePreferences() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  SetRunWhenDisabled(true);
  frc::SmartDashboard::PutString("Preferences/New File Name", "default");
  frc::SmartDashboard::PutBoolean("Preferences/Overwrite", false);
}

// Called just before this Command runs the first time
void SavePreferences::Initialize() {
  std::string file = Robot::loader.getChosenFile();
  bool overwrite = frc::SmartDashboard::GetBoolean("Preferences/Overwrite", false);
  if (file == "New"){
    std::string newFile = frc::SmartDashboard::GetString("Preferences/New File Name", "default.cfg");
    while(newFile.find("/") != std::string::npos){
      newFile.replace(1, 1, "_");
    }
    if (newFile.find(".cfg") == std::string::npos){
        newFile.append(".cfg");
    }
    file = newFile;
  }

  Robot::loader.saveConfigToFile(file, overwrite);
}

// Called repeatedly when this Command is scheduled to run
void SavePreferences::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SavePreferences::IsFinished() { return true; }

// Called once after isFinished returns true
void SavePreferences::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SavePreferences::Interrupted() {}
