/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"

#include <frc/DriverStation.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/DriveWithJoysticks.h"
#include "RobotMap.h"

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain"),
  m_front_left(DRIVE_FRONT_LEFT),
  m_front_right(DRIVE_FRONT_RIGHT),
  m_back_left(DRIVE_BACK_LEFT),
  m_back_right(DRIVE_BACK_RIGHT),
  m_left(m_front_left, m_back_left),
  m_right(m_front_right, m_back_right),
  m_drive(m_left, m_right),
  m_encoder_right(ENCODER_RIGHT_A, ENCODER_RIGHT_B),
  m_encoder_left(ENCODER_LEFT_A, ENCODER_LEFT_B, true),
  m_gyro(SerialPort::Port::kUSB1)
{
  double angular_distance = (360 / PULSES_PER_REVOLUTION) * GEARING_RATIO;
  double linear_distance = PI / 60;
  m_encoder_left.SetDistancePerPulse(linear_distance);
  m_encoder_right.SetDistancePerPulse(linear_distance);

  frc::SmartDashboard::PutData("Sensor/Gyro", &m_gyro);
}

void Drivetrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new DriveWithJoysticks());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Drivetrain::arcadeDrive(double speed, double turn){
  m_drive.ArcadeDrive(speed, turn, false);
}

void Drivetrain::curvatureDrive(double speed, double turn, bool quickTurn){
  m_drive.CurvatureDrive(speed, turn, quickTurn);
}

double Drivetrain::getDistance(int encoder){
  switch(encoder){
    case 1:
    return m_encoder_left.GetDistance();
    case 2:
    return m_encoder_right.GetDistance();
    default:
    frc::DriverStation::ReportError("Encoder does not exist.");
    return 0;
  }
}

double Drivetrain::getAngle(){
  return m_gyro.GetYaw();
}