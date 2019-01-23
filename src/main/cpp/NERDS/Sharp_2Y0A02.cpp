/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "NERDS/Sharp_2Y0A02.h"

#include <frc/Driverstation.h>

#include <cmath>

using namespace nerds;

Sharp_2Y0A02::Sharp_2Y0A02(int channel) : frc::AnalogInput(channel) {

}

double Sharp_2Y0A02::GetDistance() {
    double voltage = GetAverageVoltage();

    double a = 33.25817448287683;
    double b = -0.7187714291119961;
    double c = -9.50865904518525;

    double distance = a * pow(voltage, b) + c;

    if(distance > 60 || distance < 6){
        frc::DriverStation::ReportWarning("Distance Sensors out of Range");
        return -1;
    }

    return distance;
}