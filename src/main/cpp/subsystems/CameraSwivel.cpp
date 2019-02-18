/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSwivel.h"
#include "RobotMap.h"

CameraSwivel::CameraSwivel() : Subsystem("Camera Swivel"),
  swivel(SERVO_PWM)
{}

void CameraSwivel::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void CameraSwivel::SetServoAngle(double angle){
  swivel.SetAngle(angle);
}

double CameraSwivel::GetServoAngle() {
  return swivel.GetAngle();
}