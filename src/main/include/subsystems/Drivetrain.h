/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Encoder.h>

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

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
  void setUpMotors(ctre::phoenix::motorcontrol::can::WPI_VictorSPX&);

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX frontLeft;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX frontRight;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX backLeft;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX backRight;

  frc::SpeedControllerGroup left;
  frc::SpeedControllerGroup right;

  frc::DifferentialDrive drive;

  frc::Encoder encoderLeft;
  frc::Encoder encoderRight;

  AHRS gyro;
};
