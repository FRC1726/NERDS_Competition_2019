/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <frc/Preferences.h>
#include <frc/DriverStation.h>
#include <NetworkTables/NetworkTableInstance.h>
#include <wpi/Twine.h>
#include <sstream>
#include <string>

#include "ConfigLoader.h"

ConfigLoader::ConfigLoader() {

}

double ConfigLoader::getConfig(ParameterKey<double> config) {
    //check if exist, if not throws warning and returns default expression
    if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        std::string error = "The key you were looking for doesn't exist " + config.key + " type: double";
        frc::DriverStation::ReportWarning(error);
    }

    return frc::Preferences::GetInstance()->GetDouble(config.key, config.value);
}

int ConfigLoader::getConfig(ParameterKey<int> config) {

     if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        std::string error = "The key you were looking for doesn't exist " + config.key + " type: int";
        frc::DriverStation::ReportWarning(error);    
    }

    return frc::Preferences::GetInstance()->GetInt(config.key, config.value);
}

bool ConfigLoader::getConfig(ParameterKey<bool> config){

     if(!frc::Preferences::GetInstance()->ContainsKey(config.key)){
        std::string error = "The key you were looking for doesn't exist " + config.key + " type: boolean";
        frc::DriverStation::ReportWarning(error);    
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


bool ConfigLoader::saveConfigToFile(std::string filename){
    nt::NetworkTableInstance baseTable = nt::NetworkTableInstance::GetDefault();

    std::string error = baseTable.SaveEntries(filename, "Preferences");

    if(!error.empty()){
        frc::DriverStation::ReportError(error);
    }
}

bool ConfigLoader::loadConfigFromFile(std::string filename){
    nt::NetworkTableInstance baseTable = nt::NetworkTableInstance::GetDefault();

    std::string error = baseTable.LoadEntries(filename, "Preferences", ConfigLoader::printError);

    if(!error.empty()){
        frc::DriverStation::ReportError(error);
    }
}

void ConfigLoader::addListener(ParameterKey<double> parameter, double* value){
    
}

void ConfigLoader::printError(size_t line, const char* message){
    std::stringstream msgStream;
    msgStream << line << " " << message;
    frc::DriverStation::ReportError(msgStream.str());
}