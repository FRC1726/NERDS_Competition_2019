/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "config.h"
#include <string>
#include <vector>

class ConfigLoader {
 public:
  ConfigLoader(); 
  double getConfig(ParameterKey<double>);
  int getConfig(ParameterKey<int>);
  bool getConfig(ParameterKey<bool>);

	void savePreference(ParameterKey<int>);
	void savePreference(ParameterKey<double>);
	void savePreference(ParameterKey<bool>);

  bool saveConfigToFile(std::string);
  bool loadConfigFromFile(std::string);

 private:
	static void printError(size_t, const char*);
};
