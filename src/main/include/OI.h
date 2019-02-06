/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/buttons/JoystickButton.h>
#include <frc/Joystick.h>

class OI {
 public:
  OI();
  double getAxis(int);
  bool getDPad(int);

private:
  frc::Joystick m_driver;
  frc::JoystickButton m_button_a;
  frc::JoystickButton m_button_b;
};
