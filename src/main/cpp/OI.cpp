/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/LoadPreferences.h"
#include "commands/SavePreferences.h"
#include "commands/DeletePreferences.h"

OI::OI() {
  // Process operator interface input here.
  frc::SmartDashboard::PutData("Commands/Load Preferences", new LoadPreferences());
  frc::SmartDashboard::PutData("Commands/Save Preferences", new SavePreferences());
  frc::SmartDashboard::PutData("Commands/Delete Preferences", new DeletePreferences());
}
