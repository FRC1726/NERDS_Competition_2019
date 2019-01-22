/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TestIRSensors.h"

#include "Robot.h"
#include "RobotMap.h"
#include <frc/smartdashboard/SmartDashboard.h>

TestIRSensors::TestIRSensors() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void TestIRSensors::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TestIRSensors::Execute() {
  double Sensor_Left = Robot::drivetrain.getSensorRange(DISTANCE_SENSOR_SELECT_LEFT);
  double Sensor_Right = Robot::drivetrain.getSensorRange(DISTANCE_SENSOR_SELECT_RIGHT);
  double sensorAngle = Robot::drivetrain.getAngleToObject();

  frc::SmartDashboard::PutNumber("IR Sensor Angle", sensorAngle);
  frc::SmartDashboard::PutNumber("IR Sensor Left", Sensor_Left);
  frc::SmartDashboard::PutNumber("IR Sensor Right", Sensor_Right);
}

// Make this return true when this Command no longer needs to run execute()
bool TestIRSensors::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void TestIRSensors::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestIRSensors::Interrupted() {

}
