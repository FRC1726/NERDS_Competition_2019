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
  m_intake(LIFT_CAN_MOTOR),
  m_grabber(LIFT_SOLENOID),
  m_elevator_left(FIRST_STAGE_A, FIRST_STAGE_B),
  m_elevator_right(SECOND_STAGE_A, SECOND_STAGE_B)
{
  m_intake.ConfigPeakOutputForward(1, LIFT_TIMEOUT);
  m_intake.ConfigPeakOutputReverse(-1, LIFT_TIMEOUT);
  m_intake.ConfigNominalOutputForward(0, LIFT_TIMEOUT);
  m_intake.ConfigNominalOutputReverse(0, LIFT_TIMEOUT);
  m_intake.OverrideLimitSwitchesEnable(false);

  m_elevator_left.Set(frc::DoubleSolenoid::kForward);
  m_elevator_right.Set(frc::DoubleSolenoid::kForward);
  m_elevator_state = true;
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here. Just Do It!!!
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RunIntake());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::runMotor(double speed){
  m_intake.Set(speed);
}

void Elevator::setElevator(bool enable){
  if(enable){
    m_elevator_left.Set(frc::DoubleSolenoid::kForward);
    m_elevator_right.Set(frc::DoubleSolenoid::kForward);
    m_elevator_state = true;
  }else{
    m_elevator_left.Set(frc::DoubleSolenoid::kReverse);
    m_elevator_right.Set(frc::DoubleSolenoid::kReverse);
    m_elevator_state = false;
  }
}

bool Elevator::getElevator(){
  return m_elevator_state;
}

void Elevator::setGrabber(bool enable){
  m_grabber.Set(enable);
}

bool Elevator::getGrabber(){
  return m_grabber.Get();
}