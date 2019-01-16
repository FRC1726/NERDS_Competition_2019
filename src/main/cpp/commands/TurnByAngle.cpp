/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnByAngle.h"

#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

TurnByAngle::TurnByAngle(double target) : frc::PIDCommand("Turn To Angle", 0, 0, 0),
  timer(),
  targetAngle(target),
  PIDError(0) 
{
  Requires(&Robot::drivetrain);

  auto controller = GetPIDController();
  controller->SetContinuous(true);
  controller->SetInputRange(-180, 180);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void TurnByAngle::Initialize() {
  auto controller = GetPIDController();
  controller->SetAbsoluteTolerance(Robot::loader.getConfig(AUTOTURN_PID_TOLERANCE));
  controller->SetOutputRange(-1, 1);
  controller->SetPID(Robot::loader.getConfig(AUTOTURN_PID_PROPORTIONAL), Robot::loader.getConfig(AUTOTURN_PID_INTEGRAL), Robot::loader.getConfig(AUTOTURN_PID_DERIVATIVE));
  
  double target = Robot::drivetrain.getAngle() + targetAngle;

  if (target > 180) {
    target = (target % 360) - 180;
  } else if (target < -180) {
    target = (target % 360) + 180;     
  }
  controller->SetSetpoint(target);
  controller->Enable();  
  
  timer.Reset();
  }

// Called repeatedly when this Command is scheduled to run
void TurnByAngle::Execute() {
  double currentAngle = Robot::drivetrain.getAngle();
  double turn = driveProfile(PIDError, Robot::loader.getConfig(AUTOTURN_RANGE_MAX), Robot::loader.getConfig(AUTOTURN_RANGE_MIN));
  Robot::drivetrain.arcadeDrive(0, turn);

  SmartDashboard::PutNumber("Debug/Auto Turn/Current Angle", currentAngle);
  SmartDashboard::PutNumber("Debug/Auto Turn/Current PID", PIDError);
  SmartDashboard::PutNumber("Debug/Auto Turn/Current Speed", turn);
  }

// Make this return true when this Command no longer needs to run execute()
bool TurnByAngle::IsFinished() {
  auto controller = GetPIDController();
  if(controller->OnTarget()){
    timer.Start();
  }else{
    timer.Stop();
    timer.Reset();
  }
  
  return timer.HasPeriodPassed(Robot::loader.getConfig(AUTOTURN_PID_TIMEPERIOD)); 
  }

// Called once after isFinished returns true
void TurnByAngle::End() {
  auto controller = GetPIDController();
  controller->Reset();
  Robot::drivetrain.arcadeDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnByAngle::Interrupted() {
   auto controller = GetPIDController();
  controller->Reset();
  Robot::drivetrain.arcadeDrive(0,0);
}

void TurnByAngle::PIDWrite(double output){
  PIDError = output;
}

double TurnByAngle::PIDGet(){
  return Robot::drivetrain.getAngle();
}

double TurnByAngle::ReturnPIDInput(){
  return 0;
}

void TurnByAngle::UsePIDOutput(double output){
  
}

double TurnByAngle::driveProfile(double input, double max, double min){
  if(input == 0){
    return 0;
  }
  double absolute = fabs(input);

  double output = absolute * (max - min) + min;
  output *= output;

  if(input < 0){
    return -output;
  }else{
    return output;
  }
}
