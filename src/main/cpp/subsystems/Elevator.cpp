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
  intake(ELEVATOR_CAN_MOTOR),
  grabber(GRABBER),
  extender(EXTENDER_A, EXTENDER_B),
  launcher(LAUNCHER_A, LAUNCHER_B)
{
  intake.ConfigPeakOutputForward(1, ELEVATOR_TIMEOUT);
  intake.ConfigPeakOutputReverse(-1, ELEVATOR_TIMEOUT);
  intake.ConfigNominalOutputForward(0, ELEVATOR_TIMEOUT);
  intake.ConfigNominalOutputReverse(0, ELEVATOR_TIMEOUT);
  intake.OverrideLimitSwitchesEnable(true);
  intake.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, ELEVATOR_CAN_PID_ID, ELEVATOR_TIMEOUT);
  intake.ConfigClearPositionOnLimitR(true, ELEVATOR_TIMEOUT);

  setSensorLimits(ELEVATOR_REVERSE_SENSOR_LIMIT, ELEVATOR_FORWARD_SENSOR_LIMIT);
  intake.ConfigForwardSoftLimitEnable(true);
  intake.ConfigReverseSoftLimitEnable(true);
  intake.SetSensorPhase(false);
  intake.SetInverted(true);

  intake.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal_NormallyOpen, ELEVATOR_TIMEOUT);
  intake.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal_NormallyOpen, ELEVATOR_TIMEOUT);

  extender.Set(frc::DoubleSolenoid::kForward);
  launcher.Set(frc::DoubleSolenoid::kForward);
  extenderState = true;
  launcherState = true;
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

void Elevator::setGrabber(bool enable){
  grabber.Set(enable);
}

bool Elevator::getGrabber(){
  return grabber.Get();
}

void Elevator::setExtender(bool enable){
  if(enable){
    extender.Set(frc::DoubleSolenoid::kForward);
    extenderState = true;
  }else{
    extender.Set(frc::DoubleSolenoid::kReverse);
    extenderState = false;
  }
}

bool Elevator::getExtender(){
  return extenderState;
}

void Elevator::setLauncher(bool enable){
  if(enable){
    launcher.Set(frc::DoubleSolenoid::kForward);
    launcherState = true;
  }else{
    launcher.Set(frc::DoubleSolenoid::kReverse);
    launcherState = false;
  }
}

bool Elevator::getLauncher(){
  return launcherState;
}

void Elevator::setPID(double kP, double kI, double kD, double kF){
  intake.Config_kP(ELEVATOR_CAN_PID_ID, kP, ELEVATOR_TIMEOUT);
  intake.Config_kI(ELEVATOR_CAN_PID_ID, kI, ELEVATOR_TIMEOUT);
  intake.Config_kD(ELEVATOR_CAN_PID_ID, kD, ELEVATOR_TIMEOUT);
  intake.Config_kF(ELEVATOR_CAN_PID_ID, kF, ELEVATOR_TIMEOUT);
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

  intake.ConfigReverseSoftLimitThreshold(reverseTarget, ELEVATOR_TIMEOUT);
  intake.ConfigForwardSoftLimitThreshold(forwardTarget, ELEVATOR_TIMEOUT);
}

double Elevator::getElevatorPosition(){
  return intake.GetSelectedSensorPosition(ELEVATOR_CAN_PID_ID);
}