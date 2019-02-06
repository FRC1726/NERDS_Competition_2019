/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

#include "Commands/RunIntake.h"
#include "RobotMap.h"

Elevator::Elevator() : frc::Subsystem("Elevator"),
  intake(LIFT_CAN_MOTOR),
  grabber(LIFT_SOLENOID),
  elevatorLeft(FIRST_STAGE_A, FIRST_STAGE_B),
  elevatorRight(SECOND_STAGE_A, SECOND_STAGE_B)
{
  intake.ConfigPeakOutputForward(1, LIFT_TIMEOUT);
  intake.ConfigPeakOutputReverse(-1, LIFT_TIMEOUT);
  intake.ConfigNominalOutputForward(0, LIFT_TIMEOUT);
  intake.ConfigNominalOutputReverse(0, LIFT_TIMEOUT);
  intake.OverrideLimitSwitchesEnable(false);

  elevatorLeft.Set(frc::DoubleSolenoid::kForward);
  elevatorRight.Set(frc::DoubleSolenoid::kForward);
  elevatorState = true;
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here. Just Do It!!!
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RunIntake());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::runMotor(double speed){
  intake.Set(speed);
}

void Elevator::setElevator(bool enable){
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

bool Elevator::getElevator(){
  return elevatorState;
}

void Elevator::setGrabber(bool enable){
  grabber.Set(enable);
}

bool Elevator::getGrabber(){
  return grabber.Get();
}