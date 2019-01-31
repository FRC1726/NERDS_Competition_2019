/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "RobotMap.h"
#include "Commands/RunIntake.h"


Lift::Lift() : Subsystem("Lift"),
  lift(LIFT_CAN_MOTOR),
  grabber(LIFT_SOLENOID),
  elevatorLeft(FIRST_STAGE_A, FIRST_STAGE_B),
  elevatorRight(SECOND_STAGE_A, SECOND_STAGE_B)
{
  lift.ConfigPeakOutputForward(1, LIFT_TIMEOUT);
  lift.ConfigPeakOutputReverse(-1, LIFT_TIMEOUT);
  lift.ConfigNominalOutputForward(0, LIFT_TIMEOUT);
  lift.ConfigNominalOutputReverse(0, LIFT_TIMEOUT);
  lift.OverrideLimitSwitchesEnable(false);

  elevatorLeft.Set(frc::DoubleSolenoid::kForward);
  elevatorRight.Set(frc::DoubleSolenoid::kForward);
  elevatorState = true;
}

void Lift::InitDefaultCommand() {
  // Set the default command for a subsystem here. Just Do It!!!
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RunIntake());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Lift::runMotor(double speed){
  lift.Set(speed);
}

void Lift::setElevator(bool enable){
  if(enable){
    elevatorLeft.Set(frc::DoubleSolenoid::kForward);
    elevatorRight.Set(frc::DoubleSolenoid::kForward);
    elevatorState = true;
  }else{
    elevatorLeft.Set(frc::DoubleSolenoid::kReverse);
    elevatorRight.Set(frc::DoubleSolenoid::kReverse);
    elevatorState = false;
  }
}

bool Lift::getElevator(){
  return elevatorState;
}

void Lift::setGrabber(bool enable){
  grabber.Set(enable);
}

bool Lift::getGrabber(){
  return grabber.Get();
}