/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "RobotMap.h"
#include "Commands/RunElevator.h"

#include <ctre/phoenix/motorcontrol/FeedbackDevice.h>


Elevator::Elevator() : Subsystem("Elevator"),
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
  intake.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, LIFT_CAN_PID_ID, LIFT_TIMEOUT);

  setSensorLimits(LIFT_REVERSE_SENSOR_LIMIT, LIFT_FORWARD_SENSOR_LIMIT);
  intake.ConfigForwardSoftLimitEnable(true);
  intake.ConfigReverseSoftLimitEnable(true);

  elevatorLeft.Set(frc::DoubleSolenoid::kForward);
  elevatorRight.Set(frc::DoubleSolenoid::kForward);
  elevatorState = true;
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here. Just Do It!!!
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RunElevator());
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

void Elevator::setPID(double kP, double kI, double kD, double kF){
  intake.Config_kP(LIFT_CAN_PID_ID, kP, LIFT_TIMEOUT);
  intake.Config_kI(LIFT_CAN_PID_ID, kI, LIFT_TIMEOUT);
  intake.Config_kD(LIFT_CAN_PID_ID, kD, LIFT_TIMEOUT);
  intake.Config_kF(LIFT_CAN_PID_ID, kF, LIFT_TIMEOUT);
}

void Elevator::setElevatorSetPoint(double setPoint){
  elevatorSetPoint = setPoint;

  double target = 4096/(PI * 1.7) * setPoint;

  intake.Set(ctre::phoenix::motorcontrol::ControlMode::Position, target);
}

double Elevator::getElevatorSetPoint(){
  return elevatorSetPoint;
}

void Elevator::setSensorLimits(double reverse,double forward){
  double reverseTarget = 4096/(PI * 1.7) * reverse;
  double forwardTarget = 4096/(PI * 1.7) * forward;

  intake.ConfigReverseSoftLimitThreshold(reverseTarget, LIFT_TIMEOUT);
  intake.ConfigForwardSoftLimitThreshold(forwardTarget, LIFT_TIMEOUT);
}