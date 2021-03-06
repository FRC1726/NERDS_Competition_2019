/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>
#include <frc/buttons/JoystickButton.h>

class OI {
 public:
  OI();
  double getAxis(int);
  bool getDPad(int);

private:
  frc::Joystick driver;
  frc::JoystickButton buttonA;
  frc::JoystickButton buttonB;
};
