/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PIDTuner.h"
#include "Robot.h"
#include "config.h"
#include "frc/Timer.h"
#include "RobotMap.h"

#include "frc/smartdashboard/SmartDashboard.h"

PIDTuner::PIDTuner() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void PIDTuner::Initialize() {
  //grabs our preferences
  relaySpeed = Robot::loader.getConfig(AUTOTUNE_RELAY_SPEED);
  deadband = Robot::loader.getConfig(AUTOTUNE_TRIGGER_DEADBAND);
  Robot::drivetrain.resetGyro();

  previousAngle = 0;
  potentialPeak = 0;
  potentialValley = 0;
  findingPeak = false;
  findingValley = false;
  invert = false;
}

// Called repeatedly when this Command is scheduled to run
void PIDTuner::Execute() {

  double angle = Robot::drivetrain.getAngle();
  //compares current angle to trigger Line, sets speed to go opposite direction
  if(angle > deadband){
    invert = true;
  }else if(angle < -deadband){
    invert = false;
  }

  double speed = invert ? -relaySpeed : relaySpeed;
  Robot::drivetrain.arcadeDrive(0, speed);

  /*--------------------------------------------*/
  /*  Start of finding the peaks and valleys    */
  /*                                            */
  /*--------------------------------------------*/

  //looking for if we are above where we thing peaks will be
  if(angle > Robot::loader.getConfig(AUTOTUNE_PEAK_DEADBAND)){
    findingPeak = true;

    if(angle > potentialPeak){
          potentialPeak = angle;
    }

    //puts a valley into our array when we stop looking for valleys
    if(findingValley){
      findingValley = false;
      minValleys.push_back(std::make_pair(potentialValley, frc::Timer::GetFPGATimestamp()));
      SmartDashboard::PutNumber("Autotune/New Valley", potentialValley);
      potentialValley = 0;
    }
  }else if(angle < Robot::loader.getConfig(AUTOTUNE_VALLEY_DEADBAND)){
    findingValley = true;

    //Replaces old potential valley with new value if the new value is lower
    if(angle < potentialValley){
      potentialValley = angle;
    }

    //puts a peak into our array when we stop looking for peaks
    if(findingPeak){
      maxPeaks.push_back(std::make_pair(potentialPeak, frc::Timer::GetFPGATimestamp()));
      findingPeak = false;
      SmartDashboard::PutNumber("Autotune/New Peak", potentialPeak);
      potentialPeak = 0;
    }
  }

  /*---------------------------------------------*/
  /*start of array building for peaks and valleys*/
  /*and stable oscillation detection ------------*/
  /*---------------------------------------------*/

  if(maxPeaks.size() > Robot::loader.getConfig(AUTOTUNE_DESIRED_SAMPLES) && minValleys.size() > Robot::loader.getConfig(AUTOTUNE_DESIRED_SAMPLES)){
    for(auto peak : maxPeaks){
      if(abs(maxPeaks[0].first - peak.first) < Robot::loader.getConfig(AUTOTUNE_PEAKS_TOLERANCE)){
        stableOscillations = true;
      }else{
        stableOscillations = false;
      }
    }
    for(auto valley : minValleys){
      if(abs(minValleys[0].first - valley.first) < Robot::loader.getConfig(AUTOTUNE_VALLEY_TOLERANCE)){
        stableOscillations = true;
      }else{
        stableOscillations = false;
      }
    }
    if(!stableOscillations){
      maxPeaks.erase(maxPeaks.begin());
      minValleys.erase(minValleys.begin());
    }
  }

  /*---------------------------------------------*/
  /*-----start of actual PID math and stuff------*/
  /*---------------------------------------------*/
  /*---------------------------------------------*/


  if(stableOscillations){
    double avgPeak = 0;
    double avgPeakPeriod = 0;
    double avgValley = 0;
    double avgValleyPeriod = 0;
    double amplitude = 0;
    double Period = 0;
    double avgPeriod = 0;

    auto previousPeak = maxPeaks[0];
    for(auto peak : maxPeaks){
      avgPeak = avgPeak + peak.first;
      avgPeakPeriod += peak.second - previousPeak.second;   
      previousPeak = peak;
    }

    avgPeak = avgPeak / maxPeaks.size();
    avgPeakPeriod = avgPeakPeriod / maxPeaks.size();

    auto previousValley = minValleys[0];
    for(auto valley : minValleys){
      avgValley = avgValley + valley.first;
      avgValleyPeriod += valley.second - previousValley.second;
      previousValley = valley;
    }
    avgValley = avgValley / minValleys.size();
    avgValleyPeriod = avgValleyPeriod / minValleys.size();

    avgPeriod = (avgValleyPeriod + avgPeakPeriod) / ((maxPeaks.size() - 1) + (minValleys.size() - 1));

    amplitude = avgPeak - avgValley;

    double Pu = avgPeriod;
    double Ku = (4 * relaySpeed) / (amplitude * PI);
    double P = 0.6 * Ku;
    double I = 1.2 * (Ku / Pu);
    double D = 0.075 * Ku * Pu;

    SmartDashboard::PutNumber("PIDTuner/Amplitude", amplitude);
    SmartDashboard::PutNumber("PIDTuner/Period", avgPeriod);
    SmartDashboard::PutNumber("PIDTuner/P", P);
    SmartDashboard::PutNumber("PIDTuner/I", I);
    SmartDashboard::PutNumber("PIDTuner/D", D);
  }

} 

// Make this return true when this Command no longer needs to run execute()
bool PIDTuner::IsFinished() { return stableOscillations; }

// Called once after isFinished returns true
void PIDTuner::End() {
  Robot::drivetrain.arcadeDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDTuner::Interrupted() {
  Robot::drivetrain.arcadeDrive(0, 0);
}
