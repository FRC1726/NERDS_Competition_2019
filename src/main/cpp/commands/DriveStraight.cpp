/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveStraight.h"

#include "Robot.h"
#include "RobotMap.h"
#include <frc/smartdashboard/SmartDashboard.h>

DriveStraight::DriveStraight(double target) : frc::PIDCommand("Drive by distance", 0, 0, 0),
  driveDistance(target),
  PIDError(0)
{
  Requires(&Robot::drivetrain);
  
  auto controller = GetPIDController();
  
  controller->SetContinuous(true);
  controller->SetInputRange(-180, 180);
  controller->SetOutputRange(-1, 1);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
  encoderRightInitial = Robot::drivetrain.getDistance(ENCODER_RIGHT_SELECT);
  encoderLeftInitial = Robot::drivetrain.getDistance(ENCODER_LEFT_SELECT);
  double averageReading = (encoderRightInitial + encoderLeftInitial) / 2;

  targetDistance  = averageReading + driveDistance;
  SmartDashboard::PutNumber("Debug/Drive Straight/Target Distance", targetDistance);

  auto controller = GetPIDController();
  controller->SetAbsoluteTolerance(Robot::loader.getConfig(AUTOTURN_PID_TOLERANCE));

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
  auto controller = GetPIDController();

  double encoderLeftCurrent = Robot::drivetrain.getDistance(ENCODER_LEFT_SELECT);
  double encoderRightCurrent = Robot::drivetrain.getDistance(ENCODER_RIGHT_SELECT);
  double averageCurrent = (encoderLeftCurrent + encoderRightCurrent) / 2;

  double averageInitial = (encoderLeftInitial + encoderRightInitial) / 2;

  double distanceFromTarget = targetDistance - averageCurrent;
  double distanceMoved = averageCurrent - averageInitial;

  double acceleration = Robot::loader.getConfig(DRIVESTRAIGHT_ACCELERATION);
  double rampUp = acceleration * fabs(distanceMoved);
  double rampDown = acceleration * fabs(distanceFromTarget);

  double driveSpeed;
  if(rampUp <= rampDown){
    driveSpeed = rampUp;
  }else {
    driveSpeed = rampDown;
  }
  if(driveSpeed > 1){
    driveSpeed = 1;
  }
  if(driveSpeed < 0){
    driveSpeed = 0;
  }

  if(distanceFromTarget < 0){
    driveSpeed = -driveSpeed;
  }

  driveSpeed = driveProfile(driveSpeed, Robot::loader.getConfig(DRIVESTRAIGHT_RANGE_MAX), Robot::loader.getConfig(DRIVESTRAIGHT_RANGE_MIN));

  double currentAngle = Robot::drivetrain.getAngle();
  double turn = driveProfile(PIDError, Robot::loader.getConfig(AUTOTURN_RANGE_MAX), Robot::loader.getConfig(AUTOTURN_RANGE_MIN));
  SmartDashboard::PutNumber("Debug/Drive Straight/Ramp Up", rampUp);
  SmartDashboard::PutNumber("Debug/Drive Straight/Ramp Down", rampDown);

  if(controller->OnTarget()){
    turn = 0;
  }

  Robot::drivetrain.arcadeDrive(driveSpeed, turn);
  }

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished(){
  double currentDistance = Robot::drivetrain.getDistance(ENCODER_LEFT_SELECT);
  double tolerance = Robot::loader.getConfig(DRIVESTRAIGHT_PID_TOLERANCE);
  if(currentDistance > (targetDistance - tolerance) && currentDistance < (targetDistance + tolerance)){
    timer.Start();
  }else{
    timer.Stop();
    timer.Reset();
  }

  return timer.HasPeriodPassed(Robot::loader.getConfig(DRIVESTRAIGHT_PID_TIMEPERIOD));
}

// Called once after isFinished returns true
void DriveStraight::End() {
  auto controller = GetPIDController();
  controller->Reset();
  Robot::drivetrain.arcadeDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
   auto controller = GetPIDController();
  controller->Reset();
  Robot::drivetrain.arcadeDrive(0,0);
}

void DriveStraight::PIDWrite(double output){
  PIDError = output;
}

double DriveStraight::PIDGet(){
  return Robot::drivetrain.getAngle();
}

double DriveStraight::ReturnPIDInput(){
  return 0;
}

void DriveStraight::UsePIDOutput(double output){
  
}

double DriveStraight::driveProfile(double input, double max, double min){
  double absolute = fabs(input);

  double output = absolute * (max - min) + min;

  if(input < 0){
    return -output;
  }else{
    return output;
  }
}
