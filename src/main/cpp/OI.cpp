/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/driverStation.h>

#include "commands/DriveStraight.h"
#include "commands/DriveWithJoysticks.h"
#include "commands/LoadPreferences.h"
#include "commands/ToggleElevator.h"
#include "commands/ToggleGrabber.h"
#include "commands/TurnToHeading.h"
#include "commands/TurnByAngle.h"

#include "RobotMap.h"

OI::OI() :
  m_driver(JOYSTICK_DRIVER),
  m_button_a(&m_driver, BUTTON_A),
  m_button_b(&m_driver, BUTTON_B)
{
  //physical buttons
  m_button_a.WhenPressed(new ToggleElevator());
  m_button_b.WhenPressed(new ToggleGrabber());

  // virtual buttons.
  frc::SmartDashboard::PutData("Commands/Load Preferences", new LoadPreferences());
  frc::SmartDashboard::PutData("Commands/Arcade Drive", new DriveWithJoysticks());
  frc::SmartDashboard::PutData("Commands/Turn To Heading", new TurnToHeading(90));
  frc::SmartDashboard::PutData("Commands/Turn To Angle", new TurnByAngle(90));
  frc::SmartDashboard::PutData("Commands/Drive Straight", new DriveStraight(24));
}

double OI::getAxis(int axis){
  return m_driver.GetRawAxis(axis);
}

bool OI::getDPad(int direction) {
  //getting the angle, then returning the correct angle
  int pov = m_driver.GetPOV();

  if(pov == -1){
    return false;
  }

  switch(direction){
    case DPAD_UP:
      return pov >= 315 || pov <= 45;
    case DPAD_RIGHT:
      return pov >= 45 && pov <= 135;
    case DPAD_DOWN:
      return pov >= 135 && pov <= 225;
    case DPAD_LEFT:
      return pov >= 225 && pov <= 315;
    default:
      frc::DriverStation::ReportError("Invalid Direction");
      return false;
  }
}