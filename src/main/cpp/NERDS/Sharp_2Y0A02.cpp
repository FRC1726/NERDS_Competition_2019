/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "NERDS/Sharp_2Y0A02.h"

#include <frc/Driverstation.h>

using namespace nerds;

Sharp_2Y0A02::Sharp_2Y0A02(int channel) : frc::AnalogInput(channel) {

}

double Sharp_2Y0A02::GetDistance() {
    double voltage = GetVoltage();
    if(voltage > 4.8 || voltage < .9){
        frc::DriverStation::ReportError("Sensor value out of range");
        return -1;
    }

    double distance = 9.462/(voltage - 0.01692); //Centimeters, change to imperial like a true 'MURICAN
    return distance;
}