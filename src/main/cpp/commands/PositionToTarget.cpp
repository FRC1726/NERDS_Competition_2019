/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionToTarget.h"
#include "Robot.h"
#include "RobotMap.h"
#include <cmath>

#include "commands/DriveStraight.h"
#include "commands/TurnByAngle.h"


PositionToTarget::PositionToTarget() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void PositionToTarget::Initialize() {
  angleToTarget = Robot::drivetrain.getAngleToObject();

  double leftSensor = Robot::drivetrain.getSensorRange(DISTANCE_SENSOR_LEFT);
  double rightSensor = Robot::drivetrain.getSensorRange(DISTANCE_SENSOR_RIGHT);
  double distanceToTarget = (rightSensor + leftSensor) / 2;

  double DTS = pow(OFFSET_FROM_TARGET, 2);
  double DRS = pow(distanceToTarget, 2);
  double DT = OFFSET_FROM_TARGET;
  double DR = distanceToTarget;
  double Owo = angleToTarget * (PI/180);
  double movementDistance = pow(DTS + DRS - (2 * DT * DR) * cos(Owo), 1 / 2);
  double BS = pow(movementDistance, 2);
  double turnAngle = acos((BS + DRS-DTS) / (2 * DR * movementDistance));
  double perpendicular = 90 - turnAngle;  
  AddSequential(new TurnByAngle(turnAngle));
  AddSequential(new DriveStraight(movementDistance));
  AddSequential(new TurnByAngle(perpendicular));
}

// Called repeatedly when this Command is scheduled to run
void PositionToTarget::Execute() {
  
}

// Make this return true when this Command no longer needs to run execute()
bool PositionToTarget::IsFinished() { 
  return true; 
}

// Called once after isFinished returns true
void PositionToTarget::End() {
  Robot::drivetrain.arcadeDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionToTarget::Interrupted() {
  Robot::drivetrain.arcadeDrive(0, 0);
}
