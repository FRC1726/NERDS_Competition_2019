/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Encoder.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/VictorSP.h>

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
  frc::VictorSP m_front_left;
  frc::VictorSP m_front_right;
  frc::VictorSP m_back_left;
  frc::VictorSP m_back_right;

  frc::SpeedControllerGroup m_left;
  frc::SpeedControllerGroup m_right;

  frc::DifferentialDrive m_drive;

  frc::Encoder m_encoder_left;
  frc::Encoder m_encoder_right;

  AHRS m_gyro;
};
