#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include "../include/time.hpp"

Time::Time(char const* argTime)
{
  std::string sArgTime(argTime);
  Wakeup&& wakeup = getWakeupTime(sArgTime);
  if (wakeup == Wakeup::IMMEDIATE)
    setImmediateTime();
  if (wakeup == Wakeup::LATER_MIN)
    setTimeInMinutes(sArgTime);
  if (wakeup == Wakeup::LATER_AT_TIME)
    setFormattedTime(sArgTime);
}

Wakeup Time::getWakeupType(std::string& sArgTime) 
{
  if (sArgTime == "now")
    return Wakeup::IMMEDIATE;
  else if (sArgTime.find(':') != std::string::npos)
    return Wakeup::LATER_AT_TIME;
  else 
    return Wakeup::LATER_MIN;
}

void Time::setImmediateTime()
{
  wakeupTime_ = 0;
}

void Time::setTimeInMinutes(const std::string& sArgTime) 
{
  wakeupTime_ = std::stoi(sArgTime);
}

void Time::setFormattedTime(std::string& sArgTime)
{
  std::stringstream splitStream(sArgTime);
  size_t separatorCount = 0;
  std::string timeItem;
  while (std::getline (splitStream, timeItem, SEPARATOR)) {
    separatorCount++;
    uint32_t currentTimeItem = std::stoi(timeItem);
    if (separatorCount == 1)
      setHours(currentTimeItem);
    else if (separatorCount == 2)
      setMinutes(currentTimeItem);
    else
      setSeconds(currentTimeItem);
  }

  time_t currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  struct tm* timeMembers = gmtime(&currTime);
  if (hours_ < timeMembers->tm_hour) {
    handleError(Error::STALE_TIME);
  }
  else if (hours_ == timeMembers->tm_hour) {
    if (minutes_ < timeMembers->tm_min) {
      handleError(Error::STALE_TIME);
    }
    else if (minutes_ == timeMembers->tm_min) {
      if (seconds_ < timeMembers->tm_sec) {
        handleError(Error::STALE_TIME);
      }
      else {
        hr = 0;
        min = 0;
        sec = seconds_ - timeMembers->tim_sec;
      }
    }
    else {
      hr = 0;
      min = minutes_ - timeMembers->tm_min; 
      sec = (60 - timeMembers->tm_sec) + seconds_;
      while (sec > 60) {
        sec = sec - 60;
        min = min + 1;
      }
    }  
  }
  else {
    // TODO(raghu): 
    hr = timeMembers->tm_hour - hours_;
    min = (60 - timeMembers->tm_min) + minutes_;
    while (min > 60) {
      min = min - 60;
      hour = hour + 1;
    }
    sec = (60 - timeMembers->tm_sec) + seconds_;
    while (sec > 60) {
      sec = sec - 60;
      min = min + 1;
    }
  }
  
}

void Time::setHours(const uint32_t& hours) 
{
  hours_ = hours;
}

void Time::setMinutes(const uint32_t& minutes) 
{
  minutes_ = minutes;
}

void Time::setSeconds(const uint32_t& seconds)
{
  seconds_ = seconds;
}

uint32_t Time::getTime() 
{
  /* get current time */
  auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Current Time " << ctime(&currentTime) << std::endl;
  return wakeupTime_;
}




