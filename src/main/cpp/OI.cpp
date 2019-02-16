/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include "RobotMap.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>

#include "commands/DriveWithJoysticks.h"
#include "commands/LoadPreferences.h"
#include "commands/TurnToHeading.h"
#include "commands/TurnByAngle.h"
#include "commands/DriveStraight.h"
#include "commands/ToggleGrabber.h"
#include "commands/ToggleExtender.h"
#include "commands/ToggleLauncher.h"

OI::OI() :
  driver(JOYSTICK_DRIVER),
  buttonA(&driver, BUTTON_A),
  buttonB(&driver, BUTTON_B),
  buttonX(&driver, BUTTON_X)
{
  //physical buttons
  buttonA.WhenPressed(new ToggleExtender());
  buttonX.WhenPressed(new ToggleGrabber());
  buttonB.WhenPressed(new ToggleLauncher());

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

bool OI::getDPad(int direction) {
  //getting the angle, then returning the correct angle
  int POV = driver.GetPOV();

  if(POV == -1){
    return false;
  }

  switch(direction){
    case DPAD_UP:
      return POV >= 315 || POV <= 45;
    case DPAD_RIGHT:
      return POV >= 45 && POV <= 135;
    case DPAD_DOWN:
      return POV >= 135 && POV <= 225;
    case DPAD_LEFT:
      return POV >= 225 && POV <= 315;
    default:
      frc::DriverStation::ReportError("Invalid Direction");
      return false;
  }
}