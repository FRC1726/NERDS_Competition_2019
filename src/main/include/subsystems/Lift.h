/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DigitalInput.h>
#include <frc/VictorSP.h>

class Lift : public frc::Subsystem {
public:
  Lift();
  void InitDefaultCommand() override;
  void run(double);
private:
  frc::DigitalInput reverseLimitSwitch;
  frc::VictorSP liftMotor;
};
