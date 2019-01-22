/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "RobotMap.h"
#include <frc/DriverStation.h>
#include "commands/DriveWithJoysticks.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>

Drivetrain::Drivetrain() : Subsystem("Drivetrain"),
  frontLeft(DRIVE_FRONT_LEFT),
  frontRight(DRIVE_FRONT_RIGHT),
  backLeft(DRIVE_BACK_LEFT),
  backRight(DRIVE_BACK_RIGHT),
  left(frontLeft, backLeft),
  right(frontRight, backRight),
  drive(left, right),
  encoderRight(ENCODER_RIGHT_A, ENCODER_RIGHT_B),
  encoderLeft(ENCODER_LEFT_A, ENCODER_LEFT_B, true),
  gyro(SerialPort::Port::kUSB1),
  distanceSensorLeft(DISTANCE_SENSOR_LEFT),
  distanceSensorRight(DISTANCE_SENSOR_RIGHT)
{
  double angularDistance = (360 / PULSES_PER_REVOLUTION) * GEARING_RATIO;
  double linearDistance = PI / 60;
  encoderLeft.SetDistancePerPulse(linearDistance);
  encoderRight.SetDistancePerPulse(linearDistance);

  frc::SmartDashboard::PutData("Sensor/Gyro", &gyro);
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

double Drivetrain::getDistance(int encoder){
  switch(encoder){
    case 1:
    return encoderLeft.GetDistance();
    case 2:
    return encoderRight.GetDistance();
    default:
    frc::DriverStation::ReportError("Encoder does not exist.");
    return 0;
  }
}

double Drivetrain::getSensorRange(int sensor){
  switch(sensor){
    case 1:
    return distanceSensorLeft.GetDistance();
    case 2:
    return distanceSensorRight.GetDistance();
    default:
    frc::DriverStation::ReportError("OwO Wooks Wike Yow senso dosn't exist *poof*");
    return 0;
  }
}

double Drivetrain::getAngleToObject(){
  double left = distanceSensorLeft.GetDistance();
  double right = distanceSensorRight.GetDistance();

  if (left < 0){
  frc::DriverStation::ReportWarning("Your left sensor doesn't work");
  }
  if (right < 0){
  frc::DriverStation::ReportError("Your right sensor doesn't work");
  }

  double difference = fabs(right - left);
  double angle = atan2(difference, DISTANCE_BETWEEEN_SENSORS);
  angle = angle * (180 / PI);

  if (right < left){
    return -angle;
  } else {
    return angle; 
  }
}

double Drivetrain::getAngle(){
  return gyro.GetYaw();
}