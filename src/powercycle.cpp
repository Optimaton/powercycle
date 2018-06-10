#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <sys/reboot.h>
#include "powercycle.hpp"

Powercycle::Powercycle(const uint32_t& wakeupTime) : 
  wakeupTime_(wakeupTime) 
{
  execute();
}

void Powercycle::execute()
{   
  invokeRTC();
  shutdown();    
}

void Powercycle::invokeRTC()
{
  time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::ofstream rtcStream;
  rtcStream.open(RTC_WAKEALARM);
  rtcStream << time(&currentTime) + (wakeupTime_ * SECONDS);
  rtcStream.close();
}

/* using reboot(2) to shutdown immediately, see man reboot(2) */
void Powercycle::shutdown()
{ 
  reboot(RB_POWER_OFF);
}

