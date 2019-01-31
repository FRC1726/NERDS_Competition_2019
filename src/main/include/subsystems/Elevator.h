/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/commands/Subsystem.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>

class Lift : public frc::Subsystem {
 public:
  Lift();
  void InitDefaultCommand() override;
  void runMotor(double);
  void setElevator(bool);
  bool getElevator();
  void setfirstStage(bool);
  void setsecondStage(bool);
  bool getFirstStage();
  bool getSecondStage();

 private:
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX lift;
  frc::Solenoid elevator;
  frc::DoubleSolenoid firstStage;
  frc::DoubleSolenoid secondStage;
};