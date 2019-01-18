/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToHeading.h"

#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

TurnToHeading::TurnToHeading(double target) : frc::PIDCommand("Turn To Angle", 0, 0, 0),
  timer(),
  targetAngle(target),
  PIDError(0)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrain);

  auto controller = GetPIDController();
  controller->SetContinuous(true);
  controller->SetInputRange(-180, 180);

}

// Called just before this Command runs the first time
void TurnToHeading::Initialize() {
  auto controller = GetPIDController();
  controller->SetAbsoluteTolerance(Robot::loader.getConfig(AUTOTURN_PID_TOLERANCE));
  controller->SetOutputRange(-1, 1);
  controller->SetPID(Robot::loader.getConfig(AUTOTURN_PID_PROPORTIONAL), Robot::loader.getConfig(AUTOTURN_PID_INTEGRAL), Robot::loader.getConfig(AUTOTURN_PID_DERIVATIVE)); //Change me to preferences
  controller->SetSetpoint(targetAngle);
  controller->Enable();  
  
  timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void TurnToHeading::Execute() {
  auto controller = GetPIDController();

  double currentAngle = Robot::drivetrain.getAngle();
  double turn = driveProfile(PIDError, Robot::loader.getConfig(AUTOTURN_RANGE_MAX), Robot::loader.getConfig(AUTOTURN_RANGE_MIN));

  if(controller->OnTarget()){
    turn = 0;
  }
  
  Robot::drivetrain.arcadeDrive(0, turn);

  SmartDashboard::PutNumber("Debug/Auto Turn/Current Angle", currentAngle);
  SmartDashboard::PutNumber("Debug/Auto Turn/Current PID", PIDError);
  SmartDashboard::PutNumber("Debug/Auto Turn/Current Speed", turn);
  }

// Make this return true when this Command no longer needs to run execute()
bool TurnToHeading::IsFinished() {
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
void TurnToHeading::End() {
  auto controller = GetPIDController();
  controller->Reset();
  Robot::drivetrain.arcadeDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnToHeading::Interrupted() {
  auto controller = GetPIDController();
  controller->Reset();
  Robot::drivetrain.arcadeDrive(0,0);
}

void TurnToHeading::PIDWrite(double output){
  PIDError = output;
}

double TurnToHeading::PIDGet(){
  return Robot::drivetrain.getAngle();
}

double TurnToHeading::ReturnPIDInput(){
  return 0;
}

void TurnToHeading::UsePIDOutput(double output){
  
}

double TurnToHeading::driveProfile(double input, double max, double min){
  if(input == 0){
    return 0;
  }
  double absolute = fabs(input);

  double output = absolute * (max - min) + min;

  if(input < 0){
    return -output;
  }else{
    return output;
  }
}