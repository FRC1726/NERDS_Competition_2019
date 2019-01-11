/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/VictorSP.h>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Encoder.h>

#include <AHRS.h>

class Drivetrain : public frc::Subsystem {
public:
  Drivetrain();
  void InitDefaultCommand() override;

  void arcadeDrive(double, double);
  void curvatureDrive(double, double, bool);

  double getDistance(int);

  double getAngle();
private:
  frc::VictorSP frontLeft;
  frc::VictorSP frontRight;
  frc::VictorSP backLeft;
  frc::VictorSP backRight;

  frc::SpeedControllerGroup left;
  frc::SpeedControllerGroup right;

  frc::DifferentialDrive drive;

  frc::Encoder encoderLeft;
  frc::Encoder encoderRight;

  AHRS gyro;
};
