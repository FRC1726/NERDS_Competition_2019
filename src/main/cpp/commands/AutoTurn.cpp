/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoTurn.h"

#include "Robot.h"

AutoTurn::AutoTurn(double target) : PIDCommand(1, 0, 0),
  targetAngle(target) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrain);

  auto controller = GetPIDController();
  controller->SetContinuous(true);
  controller->SetInputRange(-180, 180);

}

// Called just before this Command runs the first time
void AutoTurn::Initialize() {
  auto controller = GetPIDController();

  controller->SetOutputRange(-1, 1);
  controller->SetPID(1,0,0); //Change me to preferences
  controller->SetSetpoint(targetAngle);
  controller->Enable();  
}

// Called repeatedly when this Command is scheduled to run
void AutoTurn::Execute() {
  double currentAngle = Robot::drivetrain.getAngle();
  PIDWrite(currentAngle);
  double turnSpeed = PIDGet();
  Robot::drivetrain.arcadeDrive(0,turnSpeed);
  }

// Make this return true when this Command no longer needs to run execute()
bool AutoTurn::IsFinished() {
  auto controller = GetPIDController();
  return controller->OnTarget();
}

// Called once after isFinished returns true
void AutoTurn::End() {
  auto controller = GetPIDController();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTurn::Interrupted() {
}