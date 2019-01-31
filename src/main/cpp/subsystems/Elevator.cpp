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
  elevator(LIFT_SOLENOID),
  firstStage(FIRST_STAGE_A, FIRST_STAGE_B),
  secondStage(SECOND_STAGE_A, SECOND_STAGE_B)
{
  lift.ConfigPeakOutputForward(1, LIFT_TIMEOUT);
  lift.ConfigPeakOutputReverse(-1, LIFT_TIMEOUT);
  lift.ConfigNominalOutputForward(0, LIFT_TIMEOUT);
  lift.ConfigNominalOutputReverse(0, LIFT_TIMEOUT);
  lift.OverrideLimitSwitchesEnable(false);
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
  elevator.Set(enable);
}

bool Lift::getElevator(){
  return elevator.Get();
}

void Lift::setfirstStage(bool enable){
  if(enable){
    firstStage.Set(frc::DoubleSolenoid::kforward);
  }else{
    firstStage.Set(frc::DoubleSolenoid::kreverse);
  }
}

void Lift::setSecondStage(bool enable){
  if(enable){
    secondStage.Set(frc::DoubleSolenoid::kforward);
  } else{
    secondStage.Set(frc::DoubleSolenoid::kreverse);
  }
}

bool Lift::getFirstStage(){
  auto status = firstStage.get();
  if(status == frc::DoubleSolenoid::kforward){
    return true;
  } else {
    return false;
  }
}

bool Lift::getSecondStage(){
auto status = secondStage.get();
  if(status == frc::DoubleSolenoid::kreverse){
    return true;
  } else {
    return false;
  }
}