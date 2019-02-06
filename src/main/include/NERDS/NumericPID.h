/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>

#include <frc/PIDSource.h>
#include <frc/PIDOutput.h>
#include <frc/PIDController.h>


class NumericPID : public frc::PIDSource, public frc::PIDOutput {
 public:
  NumericPID(double, double, double);
  void PIDWrite(double) override;
  double PIDGet() override;

  double Get();
  void Write(double);

  std::shared_ptr<frc::PIDController> GetController();

protected:


private:
  std::shared_ptr<frc::PIDController> controller;

  double m_pid_input;
  double m_pid_error;
};
