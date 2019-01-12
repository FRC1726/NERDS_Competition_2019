/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CurvatureWithJoysticks.h"
#include "Robot.h"
#include "RobotMap.h"
#include <cmath>
CurvatureWithJoysticks::CurvatureWithJoysticks() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void CurvatureWithJoysticks::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CurvatureWithJoysticks::Execute() { 
  double speed = Robot::oi.getAxis(AXIS_LEFT_X);
  double turn = Robot::oi.getAxis(AXIS_RIGHT_Y);
  
  speed = applyDeadZone(speed, Robot::loader.getConfig(JOYSTICK_DRIVE_DEADZONE));
  turn = applyDeadZone(turn, Robot::loader.getConfig(JOYSTICK_DRIVE_DEADZONE));

  speed = driveProfile(speed, Robot::loader.getConfig(JOYSTICK_DRIVE_MAX), Robot::loader.getConfig(JOYSTICK_DRIVE_MIN));
  turn = driveProfile(turn, Robot::loader.getConfig(JOYSTICK_DRIVE_MAX), Robot::loader.getConfig(JOYSTICK_DRIVE_MIN));

  bool quickTurn;
  if(turn < Robot::loader.getConfig(JOYSTICK_DRIVE_QUICK_TURN)){
    quickTurn = true;
  }else{
    quickTurn = false;
  }

  Robot::drivetrain.curvatureDrive(speed, turn, quickTurn);
}

// Make this return true when this Command no longer needs to run execute()
bool CurvatureWithJoysticks::IsFinished() { return false; }

// Called once after isFinished returns true
void CurvatureWithJoysticks::End() {
  Robot::drivetrain.curvatureDrive(0, 0, false);
}


// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CurvatureWithJoysticks::Interrupted() {
  Robot::drivetrain.curvatureDrive(0, 0, false);
}

double CurvatureWithJoysticks::applyDeadZone(double input, double deadzone){
  double absolute = fabs(input);

  if(absolute < deadzone) {
   return 0;
  }

  double normalized = (absolute - deadzone)/(1 - deadzone);
  
  if(input < 0){
    return -normalized;
  }else{
    return normalized;
  }
}

double CurvatureWithJoysticks::driveProfile(double input, double max, double min){
  double absolute = fabs(input);

  double output = absolute * (max - min) + min;
  output *= output;

  if(input < 0){
    return -output;
  }else{
    return output;
  }
}
