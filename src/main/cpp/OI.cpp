/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include "RobotMap.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/DriveWithJoysticks.h"
#include "commands/CurvatureWithJoysticks.h"
#include "commands/LoadPreferences.h"

OI::OI() :
  driver(JOYSTICK_DRIVER)
{
  // Process operator interface input here.
  frc::SmartDashboard::PutData("Commands/Load Preferences", new LoadPreferences());
  frc::SmartDashboard::PutData("Commands/Arcade Drive", new DriveWithJoysticks());
  frc::SmartDashboard::PutData("Commands/Curvature Drive", new CurvatureWithJoysticks());
}

double OI::getAxis(int axis){
  return driver.GetRawAxis(axis);
}