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
  rtcStream.open("/sys/class/rtc/rtc0/wakealarm");
  rtcStream << time(&currentTime) + (wakeupTime_ * SECONDS);
  rtcStream.close();
}

/* shuts down system by forking a shell and executing shutdown command */
void Powercycle::shutdown()
{ 
  reboot(RB_POWER_OFF);
}

