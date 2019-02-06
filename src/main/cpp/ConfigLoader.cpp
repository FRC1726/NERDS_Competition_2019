/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <frc/Preferences.h>

#include <sstream>

#include <frc/DriverStation.h>
#include <NetworkTables/NetworkTableInstance.h>
#include <wpi/Twine.h>

#include "ConfigLoader.h"

ConfigLoader::ConfigLoader() {

}

double ConfigLoader::getConfig(ParameterKey<double> config) {
    //check if exist, if not throws warning and returns default expression
    if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        frc::DriverStation::ReportWarning("the key you were looking for doesn't exist. we substituted our own! -double not detected");
    }

    return frc::Preferences::GetInstance()->GetDouble(config.key, config.value);
}

int ConfigLoader::getConfig(ParameterKey<int> config) {

     if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        frc::DriverStation::ReportWarning("the key you were looking for doesn't exist. we substituted our own! -integer not detected");
    }

    return frc::Preferences::GetInstance()->GetInt(config.key, config.value);
}

bool ConfigLoader::getConfig(ParameterKey<bool> config){

     if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        frc::DriverStation::ReportWarning("the key you were looking for doesn't exist. we substituted our own! -boolean not detected");
    }

    return frc::Preferences::GetInstance()->GetBoolean(config.key, config.value);
}

void ConfigLoader::savePreference(ParameterKey<int> param){
    if(!frc::Preferences::GetInstance()->ContainsKey(param.key))
        frc::Preferences::GetInstance()->PutInt(param.key, param.value);
}

void ConfigLoader::savePreference(ParameterKey<bool> param){
    if(!frc::Preferences::GetInstance()->ContainsKey(param.key))
        frc::Preferences::GetInstance()->PutBoolean(param.key, param.value);
}

void ConfigLoader::savePreference(ParameterKey<double> param){
    if(!frc::Preferences::GetInstance()->ContainsKey(param.key))
        frc::Preferences::GetInstance()->PutDouble(param.key, param.value);
}


bool ConfigLoader::saveConfigToFile(std::string file_name){
    nt::NetworkTableInstance base_table = nt::NetworkTableInstance::GetDefault();

    std::string error = base_table.SaveEntries(file_name, "Preferences");

    if(!error.empty()){
        frc::DriverStation::ReportError(error);
    }
}

bool ConfigLoader::loadConfigFromFile(std::string file_name){
    nt::NetworkTableInstance base_table = nt::NetworkTableInstance::GetDefault();

    std::string error = base_table.LoadEntries(file_name, "Preferences", ConfigLoader::printError);

    if(!error.empty()){
        frc::DriverStation::ReportError(error);
    }
}

void ConfigLoader::printError(size_t line, const char* message){
    std::stringstream msg_stream;
    msg_stream << line << " " << message;
    frc::DriverStation::ReportError(msg_stream.str());
}