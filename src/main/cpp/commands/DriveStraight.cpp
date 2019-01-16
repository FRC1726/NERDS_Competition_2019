/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveStraight.h"

#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

DriveStraight::DriveStraight(double target) : frc::PIDCommand("Drive by distance", 0, 0, 0),
  driveDistance(target),
  PIDError(0)
{
  Requires(&Robot::drivetrain)
  
  auto controller = GetPIDController();
  controller->SetContinuous(true);
  controller->SetInputRange(-180, 180);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
  double currentDistance = Robot::drivetrain.GetDistance(ENCODER_LEFT_SELECT);
  targetDistance  = currentDistance + driveDistance;

  auto controller = GetPIDController();
  controller->SetAbsoluteTolerance(Robot::loader.getConfig(AUTOTURN_PID_TOLERANCE));
  controller->SetOutputRange(-1, 1);

  double p = Robot::loader.getConfig(AUTOTURN_PID_PROPORTIONAL);
  double i = Robot::loader.getConfig(AUTOTURN_PID_INTEGRAL);
  double d = Robot::loader.getConfig(AUTOTURN_PID_DERIVATIVE);
  controller->SetPID(p, i, d);

  double target = Robot::drivetrain.getAngle();
  controller->SetSetpoint(target);
  controller->Enable();  
  
  timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
  double currentDistance = Robot::drivetrain.GetDistance(ENCODER_LEFT_SELECT);
  double driveSpeed;
  double acceleration = Robot::loader.getConfig(DRIVESTRAIGHT_ACCELERATION);
  double deceleration = Robot::loader.getConfig(DRIVESTRAIGHT_ACCELERATION) * -1;
  double rampUp = acceleration * (target - currentDistance);
  double rampDown = 0 //Define me!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  double currentAngle = Robot::drivetrain.getAngle();
  double turn = driveProfile(PIDError, Robot::loader.getConfig(DRIVESTRAIGHT_RANGE_MAX), Robot::loader.getConfig(DRIVESTRAIGHT_RANGE_MIN));
  Robot::drivetrain.arcadeDrive(driveSpeed, turn);
  }

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveStraight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {}
