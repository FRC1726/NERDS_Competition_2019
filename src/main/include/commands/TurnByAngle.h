/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/PIDCommand.h>

#include <frc/Timer.h>

class TurnByAngle : public frc::PIDCommand {
 public:
  TurnByAngle(double);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

  void PIDWrite(double) override;
  double PIDGet() override;

  double driveProfile(double, double, double);

private:
  double wrapAngle(double);
  frc::Timer m_timer;

  double m_target_angle;
  double m_pid_error;

protected:
  double ReturnPIDInput() override;
  void UsePIDOutput(double) override;
};