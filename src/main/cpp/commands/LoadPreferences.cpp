/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LoadPreferences.h"

#include "config.h"
#include "Robot.h"

LoadPreferences::LoadPreferences() : frc::Command("Load Preferences") {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void LoadPreferences::Initialize() {
  //Joysticks
  Robot::loader.savePreference(JOYSTICK_DRIVE_MAX);
  Robot::loader.savePreference(JOYSTICK_DRIVE_MIN);
  Robot::loader.savePreference(JOYSTICK_TURN_MAX);
  Robot::loader.savePreference(JOYSTICK_TURN_MIN);
  Robot::loader.savePreference(JOYSTICK_DRIVE_DEADZONE);
  Robot::loader.savePreference(JOYSTICK_REVERSE_FORWARD);

  //AutoTurn
  Robot::loader.savePreference(AUTOTURN_RANGE_MAX);
  Robot::loader.savePreference(AUTOTURN_RANGE_MIN);
  Robot::loader.savePreference(AUTOTURN_PID_PROPORTIONAL);
  Robot::loader.savePreference(AUTOTURN_PID_INTEGRAL);
  Robot::loader.savePreference(AUTOTURN_PID_DERIVATIVE);
  Robot::loader.savePreference(AUTOTURN_PID_TOLERANCE);
  Robot::loader.savePreference(AUTOTURN_PID_TIMEPERIOD);

  //DriveStraight
  Robot::loader.savePreference(DRIVESTRAIGHT_RANGE_MAX);
  Robot::loader.savePreference(DRIVESTRAIGHT_RANGE_MIN);
  Robot::loader.savePreference(DRIVESTRAIGHT_ACCELERATION);
  Robot::loader.savePreference(DRIVESTRAIGHT_PID_TIMEPERIOD);
  Robot::loader.savePreference(DRIVESTRAIGHT_PID_TOLERANCE);

  //Lift
  Robot::loader.savePreference(LIFT_RUN_SPEED);
}

// Called repeatedly when this Command is scheduled to run
void LoadPreferences::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool LoadPreferences::IsFinished() { return true; }

// Called once after isFinished returns true
void LoadPreferences::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LoadPreferences::Interrupted() {}
