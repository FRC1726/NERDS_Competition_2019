/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <VictorSP.h>
#include <DifferentialDrive.h>
#include SpeedControllerGroup.h

class Drivetrain : public frc::Subsystem {
public:
  Drivetrain();
  void InitDefaultCommand() override;

  void arcadeDrive(double, double);
  void curvatureDrive(double, double, bool);

private:
  VictorSP frontLeft;
  VictorSP frontRight;
  VictorSP backLeft;
  VictorSP backRight;

  SpeedControllerGroup left;
  SpeedControllerGroup right;

  DifferentialDrive drive;
};
