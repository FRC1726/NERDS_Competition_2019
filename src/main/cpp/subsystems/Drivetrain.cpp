/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "RobotMap.h"

#include "commands/DriveWithJoysticks.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain"),
  frontLeft(DRIVE_FRONT_LEFT),
  frontRight(DRIVE_FRONT_RIGHT),
  backLeft(DRIVE_BACK_LEFT),
  backRight(DRIVE_BACK_RIGHT),
  left(frontLeft, backLeft),
  right(frontRight, backRight),
  drive(left, right)
{

}

void Drivetrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new DriveWithJoysticks());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Drivetrain::arcadeDrive(double speed, double turn){
  drive.ArcadeDrive(speed, turn, false);
}

void Drivetrain::curvatureDrive(double speed, double turn, bool quickTurn){
  drive.CurvatureDrive(speed, turn, quickTurn);
}