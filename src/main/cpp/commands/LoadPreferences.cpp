/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LoadPreferences.h"

#include "Robot.h"
#include "config.h"

#include <frc/smartdashboard/SmartDashboard.h>

LoadPreferences::LoadPreferences() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  SetRunWhenDisabled(true);
  frc::SmartDashboard::PutBoolean("Preferences/Overwrite", false);
}

// Called just before this Command runs the first time
void LoadPreferences::Initialize() {
  bool overwrite = frc::SmartDashboard::GetBoolean("Preferences/Overwrite", false);
  Robot::loader.loadConfigFromFile(Robot::loader.getChosenFile(), overwrite);
}

// Called repeatedly when this Command is scheduled to run
void LoadPreferences::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool LoadPreferences::IsFinished() { return true; }

// Called once after isFinished returns true
void LoadPreferences::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LoadPreferences::Interrupted() {}
