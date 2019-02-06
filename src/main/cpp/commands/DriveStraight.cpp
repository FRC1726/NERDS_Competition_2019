/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveStraight.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"
#include "RobotMap.h"

DriveStraight::DriveStraight(double target) : frc::PIDCommand("Drive by distance", 0, 0, 0),
  m_drive_distance(target),
  m_pid_error(0)
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
  m_encoder_right_initial = Robot::drivetrain.getDistance(ENCODER_RIGHT_SELECT);
  m_encoder_left_initial = Robot::drivetrain.getDistance(ENCODER_LEFT_SELECT);
  double average_reading = (m_encoder_right_initial + m_encoder_left_initial) / 2;

  m_target_distance  = average_reading + m_drive_distance;
  SmartDashboard::PutNumber("Debug/Drive Straight/Target Distance", m_target_distance);

  auto controller = GetPIDController();
  controller->SetAbsoluteTolerance(Robot::loader.getConfig(AUTOTURN_PID_TOLERANCE));

  double p = Robot::loader.getConfig(AUTOTURN_PID_PROPORTIONAL);
  double i = Robot::loader.getConfig(AUTOTURN_PID_INTEGRAL);
  double d = Robot::loader.getConfig(AUTOTURN_PID_DERIVATIVE);
  controller->SetPID(p, i, d);

  double target = Robot::drivetrain.getAngle();
  controller->SetSetpoint(target);
  controller->Enable();  
  
  m_timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
  auto controller = GetPIDController();

  double encoder_left_current = Robot::drivetrain.getDistance(ENCODER_LEFT_SELECT);
  double encoder_right_current = Robot::drivetrain.getDistance(ENCODER_RIGHT_SELECT);
  double average_current = (encoder_left_current + encoder_right_current) / 2;

  double average_initial = (m_encoder_left_initial + m_encoder_right_initial) / 2;

  double distance_from_target = m_target_distance - average_current;
  double distance_moved = average_current - average_initial;

  double acceleration = Robot::loader.getConfig(DRIVESTRAIGHT_ACCELERATION);
  double ramp_up = acceleration * fabs(distance_moved);
  double ramp_down = acceleration * fabs(distance_from_target);

  double drive_speed;
  if(ramp_up <= ramp_down){
    drive_speed = ramp_up;
  }else {
    drive_speed = ramp_down;
  }
  if(drive_speed > 1){
    drive_speed = 1;
  }
  if(drive_speed < 0){
    drive_speed = 0;
  }

  if(distance_from_target < 0){
    drive_speed = -drive_speed;
  }

  drive_speed = driveProfile(drive_speed, Robot::loader.getConfig(DRIVESTRAIGHT_RANGE_MAX), Robot::loader.getConfig(DRIVESTRAIGHT_RANGE_MIN));

  double current_angle = Robot::drivetrain.getAngle();
  double turn = driveProfile(m_pid_error, Robot::loader.getConfig(AUTOTURN_RANGE_MAX), Robot::loader.getConfig(AUTOTURN_RANGE_MIN));
  SmartDashboard::PutNumber("Debug/Drive Straight/Ramp Up", ramp_up);
  SmartDashboard::PutNumber("Debug/Drive Straight/Ramp Down", ramp_down);

  if(controller->OnTarget()){
    turn = 0;
  }

  Robot::drivetrain.arcadeDrive(drive_speed, turn);
  }

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished(){
  double current_distance = Robot::drivetrain.getDistance(ENCODER_LEFT_SELECT);
  double tolerance = Robot::loader.getConfig(DRIVESTRAIGHT_PID_TOLERANCE);
  if(current_distance > (m_target_distance - tolerance) && current_distance < (m_target_distance + tolerance)){
    m_timer.Start();
  }else{
    m_timer.Stop();
    m_timer.Reset();
  }

  return m_timer.HasPeriodPassed(Robot::loader.getConfig(DRIVESTRAIGHT_PID_TIMEPERIOD));
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
  m_pid_error = output;
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
