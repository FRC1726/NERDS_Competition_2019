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
#include <cstdio>
#include <frc/smartdashboard/SmartDashboard.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>

#include "ConfigLoader.h"

ConfigLoader::ConfigLoader() {
    populateChoices();
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


bool ConfigLoader::saveConfigToFile(std::string filename, bool overwrite){
    std::string filepath = "/home/lvuser/deploy/";
    filepath.append(filename);
    if (overwrite && fileExists(filepath)){
        int status = std::remove(filepath.c_str());
        if(status){
            frc::DriverStation::ReportError("Could not delete old config file");
            return false;
        }
    }

    nt::NetworkTableInstance baseTable = nt::NetworkTableInstance::GetDefault();
    auto preferencesTable = baseTable.GetTable("Preferences");
    auto error = preferencesTable->SaveEntries(filepath);

    if(error){
        frc::DriverStation::ReportError(error);
        return false;
    }
    return true;
}

bool ConfigLoader::loadConfigFromFile(std::string filename, bool overwrite){
    std::string filepath = "/home/lvuser/deploy/";
    filepath.append(filename);

    if(!fileExists(filepath)){
        frc::DriverStation::ReportError("Owo It seems the conig file doesn't exist");
       return false;
    }

    nt::NetworkTableInstance baseTable = nt::NetworkTableInstance::GetDefault();
    auto preferencesTable = baseTable.GetTable("Preferences");

    if(overwrite){
        preferencesTable->GetInstance().DeleteAllEntries();
    }

    auto error = preferencesTable->LoadEntries(filepath, ConfigLoader::printError);

    if(error){
        frc::DriverStation::ReportError(error);
    }
}

void ConfigLoader::printError(size_t line, const char* message){
    std::stringstream msgStream;
    msgStream << line << " " << message;
    frc::DriverStation::ReportError(msgStream.str());
}

bool ConfigLoader::fileExists(const std::string& filePath) {
    std::ifstream f(filePath.c_str());
    return f.good();
}

void ConfigLoader::populateChoices(){
    DIR* dirp = opendir("/home/lvuser/deploy/");
    struct dirent * dp;

    frc::SendableChooser<std::string>*newChooser = new frc::SendableChooser<std::string>();

    while ((dp = readdir(dirp)) != NULL) {
        std::string filename = dp->d_name;

        if(filename.find(".") != 0){
            newChooser->AddOption(filename, filename);
        }
    }
    closedir(dirp);

    fileChooser.reset(newChooser);

    frc::SmartDashboard::PutData("Preferences/files", fileChooser.get());
}