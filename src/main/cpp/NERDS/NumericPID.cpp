/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "NERDS/NumericPID.h"

NumericPID::NumericPID(double p, double i, double d) :
    controller(new frc::PIDController(p, i, d, this, this)),
    m_pid_input(0),
    m_pid_error(0)
{

}

void NumericPID::PIDWrite(double output){
    m_pid_error = output;
}

double NumericPID::PIDGet(){
    return m_pid_input;
}

void NumericPID::Write(double input){
    m_pid_input = input;
}

double NumericPID::Get(){
    return m_pid_error;
}

std::shared_ptr<frc::PIDController> NumericPID::GetController(){
    return controller;
}