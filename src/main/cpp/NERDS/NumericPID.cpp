/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "NERDS/NumericPID.h"

NumericPID::NumericPID(double p, double i, double d) :
    controller(new frc::PIDController(p, i, d, this, this)),
    PIDInput(0),
    PIDError(0)
{

}

void NumericPID::PIDWrite(double output){
    PIDError = output;
}

double NumericPID::PIDGet(){
    return PIDInput;
}

void NumericPID::Write(double input){
    PIDInput = input;
}

double NumericPID::Get(){
    return PIDError;
}

std::shared_ptr<frc::PIDController> NumericPID::GetController(){
    return controller;
}