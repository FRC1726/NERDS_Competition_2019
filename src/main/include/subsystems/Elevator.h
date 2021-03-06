/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/commands/Subsystem.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>

class Elevator : public frc::Subsystem {
 public:
  Elevator();
  void InitDefaultCommand() override;
  void runMotor(double);
  void setElevator(bool);
  bool getElevator();
  void setGrabber(bool);
  bool getGrabber();

 private:
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX intake;

  frc::Solenoid grabber;

  frc::DoubleSolenoid elevatorLeft;
  frc::DoubleSolenoid elevatorRight;
  bool elevatorState;
};
