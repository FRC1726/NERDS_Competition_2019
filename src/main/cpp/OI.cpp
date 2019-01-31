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
#include "commands/LoadPreferences.h"
#include "commands/TurnToHeading.h"
#include "commands/TurnByAngle.h"
#include "commands/DriveStraight.h"
#include "commands/ToggleElevator.h"
#include "commands/ToggleGrabber.h"

OI::OI() :
  driver(JOYSTICK_DRIVER),
  buttonA(&driver, BUTTON_A),
  buttonB(&driver, BUTTON_B)
{
  //physical buttons
  buttonA.WhenPressed(new ToggleElevator());
  buttonB.WhenPressed(new ToggleGrabber());

  // virtual buttons.
  frc::SmartDashboard::PutData("Commands/Load Preferences", new LoadPreferences());
  frc::SmartDashboard::PutData("Commands/Arcade Drive", new DriveWithJoysticks());
  frc::SmartDashboard::PutData("Commands/Turn To Heading", new TurnToHeading(90));
  frc::SmartDashboard::PutData("Commands/Turn To Angle", new TurnByAngle(90));
  frc::SmartDashboard::PutData("Commands/Drive Straight", new DriveStraight(24));
}

double OI::getAxis(int axis){
  return driver.GetRawAxis(axis);
}