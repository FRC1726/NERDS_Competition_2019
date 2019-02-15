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

class Elevator : public frc::Subsystem {
 public:
  Elevator();
  void InitDefaultCommand() override;
  void runMotor(double);

  void setElevator(bool);
  bool getElevator();

  void setGrabber(bool);
  bool getGrabber();

  void setPID(double, double, double, double);

  void setElevatorSetPoint(double);
  double getElevatorSetPoint();

 private:
  void setSensorLimits(double, double);

  ctre::phoenix::motorcontrol::can::WPI_TalonSRX intake;

  frc::Solenoid grabber;

  frc::DoubleSolenoid elevatorLeft;
  frc::DoubleSolenoid elevatorRight;
  bool elevatorState;

  double elevatorSetPoint;
};
