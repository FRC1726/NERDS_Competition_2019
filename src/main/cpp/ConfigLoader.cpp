/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <frc/Preferences.h>
#include <frc/DriverStation.h>

#include "ConfigLoader.h"

ConfigLoader::ConfigLoader() {

}
double ConfigLoader::getConfig(ParameterKey<double> config) {
    //check if exist, if not throws warning and returns default expression
    if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        frc::DriverStation::ReportWarning("OwO it appeaws that the key you wewe wooking fow doesn't exist. Ow- we substituted ouw own! -double ");
    }

    return frc::Preferences::GetInstance()->GetDouble(config.key, config.value);
}
int ConfigLoader::getConfig(ParameterKey<int> config) {

     if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        frc::DriverStation::ReportWarning("OwO it appeaws that the key you wewe wooking fow doesn't exist. Ow- we substituted ouw own! -integer");
    }

    return frc::Preferences::GetInstance()->GetInt(config.key, config.value);
}
bool ConfigLoader::getConfig(ParameterKey<bool> config){

     if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        frc::DriverStation::ReportWarning("OwO it appeaws that the key you wewe wooking fow doesn't exist. Ow- we substituted ouw own! -boolean");
    }

    return frc::Preferences::GetInstance()->GetBoolean(config.key, config.value);
}