/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Lift.h"

#include "commands/Runlift.h"
#include "RobotMap.h"

Lift::Lift() : frc::Subsystem("Lift"), 
  m_reverse_limit_switch(LIFT_REVERSE_LIMIT_SWITCH),
  m_lift_motor(LIFT_MOTOR)
{

}

void Lift::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RunLift());
}

void Lift::run(double speed) {
  m_lift_motor.Set(speed);
}
