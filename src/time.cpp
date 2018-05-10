#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <cstdint>
#include "time.hpp"

Time::Time(char const* argTime)
{
  std::string sArgTime(argTime);
  Wakeup&& wakeup = getWakeupType(sArgTime);
  if (wakeup == Wakeup::IMMEDIATE)
    setImmediateTime();
  if (wakeup == Wakeup::LATER_MIN)
    setTimeInMinutes(sArgTime);
  if (wakeup == Wakeup::LATER_AT_TIME)
    setFormattedTime(sArgTime);
}

Wakeup Time::getWakeupType(const std::string& sArgTime) 
{
  if (sArgTime == "now")
    return Wakeup::IMMEDIATE;
  else if (sArgTime.find(SEPARATOR) != std::string::npos)
    return Wakeup::LATER_AT_TIME;
  else 
    return Wakeup::LATER_MIN;
}

void Time::setWakeupTime(uint32_t wakeupTime) 
{
  wakeupTime_ = wakeupTime;
}

void Time::setImmediateTime()
{
  setWakeupTime(0);
}

void Time::setTimeInMinutes(const std::string& sArgTime) 
{
  setWakeupTime(std::stoi(sArgTime));
}

void Time::setFormattedTime(const std::string& sArgTime)
{
  std::stringstream splitStream(sArgTime);
  size_t separatorCount = 0;
  std::string timeItem;
  while (std::getline (splitStream, timeItem, SEPARATOR)) {
    separatorCount++;
    uint32_t currentTimeItem = std::stoi(timeItem);
    if (separatorCount == static_cast<size_t>(Separator::HOUR))
      setHours(currentTimeItem);
    else if (separatorCount == static_cast<size_t>(Separator::MIN))
      setMinutes(currentTimeItem);
    else
      setSeconds(currentTimeItem);
  }
  convertToMinutes();
}

void Time::convertToMinutes()
{
  uint32_t hr, min, sec;
  time_t currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  struct tm* timeMembers = localtime(&currTime);
  std::cout << timeMembers->tm_hour << std::endl;
  long systemTime = (timeMembers->tm_hour * HR_SEC) + (timeMembers->tm_min * MIN_SEC) + timeMembers->tm_sec; /* in seconds */
  long alarmTime = (hours_ * HR_SEC) + (minutes_ * MIN_SEC) + seconds_; /* in seconds */
  std::cout << alarmTime - systemTime << std::endl;
  if ((alarmTime - systemTime) < 0)
    handleError(TError::STALE_TIME);
  else
    setWakeupTime((alarmTime - systemTime)/SEC_MIN);
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

uint32_t Time::getWakeupTime() 
{
  /* get current time */
  return wakeupTime_;
}

/* handle generic error */
void Time::handleError(const TError err)
{
  std::string errorMsg;
  if (err == TError::STALE_TIME)
    errorMsg = "Command Failed. Stale Time Provided.";
  std::cout << errorMsg << std::endl;
  std::exit(EXIT_FAILURE);
}



