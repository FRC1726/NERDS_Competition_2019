/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunElevator.h"

#include "Robot.h"
#include "RobotMap.h"
#include "config.h"

#include <frc/smartdashboard/SmartDashboard.h>

RunElevator::RunElevator() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());

  Requires(&Robot::elevator);
}

// Called just before this Command runs the first time
void RunElevator::Initialize() {
  double p = Robot::loader.getConfig(ELEVATOR_P);
  double i = Robot::loader.getConfig(ELEVATOR_I);
  double d = Robot::loader.getConfig(ELEVATOR_D);
  double f = Robot::loader.getConfig(ELEVATOR_F);
  Robot::elevator.setPID(p, i, d, f);
}

// Called repeatedly when this Command is scheduled to run
void RunElevator::Execute() {
  
  double maxSpeed = Robot::loader.getConfig(ELEVATOR_MAX_SPEED);

  double forward = Robot::oi.getAxis(AXIS_RIGHT_TRIGGER);
  double backward = Robot::oi.getAxis(AXIS_LEFT_TRIGGER);

  double speed = forward - backward;

  double setPoint = Robot::elevator.getElevatorSetPoint();

  setPoint += speed * maxSpeed;

  /*if (setPoint < ELEVATOR_REVERSE_SENSOR_LIMIT){
    setPoint = ELEVATOR_REVERSE_SENSOR_LIMIT;
  } else if (setPoint > ELEVATOR_FORWARD_SENSOR_LIMIT){
    setPoint = ELEVATOR_FORWARD_SENSOR_LIMIT;
  }

  Robot::elevator.setElevatorSetPoint(setPoint);*/

  Robot::elevator.runMotor(speed * maxSpeed);
  SmartDashboard::PutNumber("Debug/Elevator Position", Robot::elevator.getElevatorPosition());
  SmartDashboard::PutNumber("Debug/Elevator Setpoint", setPoint);
}

// Make this return true when this Command no longer needs to run execute()
bool RunElevator::IsFinished() {
   return false; 
}

// Called once after isFinished returns true
void RunElevator::End() {
  Robot::elevator.runMotor(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunElevator::Interrupted() {
  Robot::elevator.runMotor(0);

}
