/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Servo.h>

class CameraSwivel : public frc::Subsystem {

public:
  CameraSwivel();
  void InitDefaultCommand() override;

  void SetServoAngle(double);
  double GetServoAngle();

private:
  frc::Servo swivel;
};
