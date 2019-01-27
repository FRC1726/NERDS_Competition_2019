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

  Robot::drivetrain.arcadeDrive(0,relaySpeed);
  previousAngle = 0;
  potentialPeak = 0;
  findingPeak = false;
  findingValley = false;

}

// Called repeatedly when this Command is scheduled to run
void PIDTuner::Execute() {

  double angle = Robot::drivetrain.getAngle();
  double speed;
  //compares current angle to trigger Line, sets speed to go opposite direction
  if(angle > deadband){
    speed = -relaySpeed;
  }else if(angle < -deadband){
    speed = relaySpeed;
  }
  Robot::drivetrain.arcadeDrive(0,speed);


  /*--------------------------------------------*/
  /*  Start of finding the peaks and valleys    */
  /*                                            */
  /*--------------------------------------------*/

  //looking for if we are above where we thing peaks will be
  if(angle > Robot::loader.getConfig(AUTOTUNE_PEAK_DEADBAND)){
    //puts a valley into our array when we stop looking for valleys
    if(findingValley){
      findingValley = false;
      minValleys.push_back(std::make_pair(potentialValley, frc::Timer::GetFPGATimestamp()));
    }
    findingPeak = true;
    //finds potential Peaks
    if(angle > potentialPeak){
      potentialPeak = angle;
    }
  }else if(angle < Robot::loader.getConfig(AUTOTUNE_VALLEY_DEADBAND)){
    //puts a peak into our array when we stop looking for peaks
    if(findingPeak){
      maxPeaks.push_back(std::make_pair(potentialPeak, frc::Timer::GetFPGATimestamp()));
      findingPeak = false;
    }
    findingValley = true;
    //finds potential valleys
    if(angle < potentialValley){
      potentialValley = angle;
    }
  // puts everything in a safe place in case program poops itself
  }else{
    findingPeak = false;
    findingValley = false;
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
    for(auto peak : maxPeaks){
      avgPeak = avgPeak + peak.first;
    }
    avgPeak = avgPeak / maxPeaks.size();
    avgPeakPeriod = avgPeakPeriod / maxPeaks.size();
    for(auto valley : minValleys){
      avgValley = avgValley + valley.first;
    }

    avgValley = avgValley / minValleys.size();
    avgValleyPeriod = avgValleyPeriod / minValleys.size();
    amplitude = avgPeak - avgValley;


  }
  
}

// Make this return true when this Command no longer needs to run execute()
bool PIDTuner::IsFinished() { return false; }

// Called once after isFinished returns true
void PIDTuner::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDTuner::Interrupted() {}
