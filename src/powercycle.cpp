#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include "powercycle.hpp"

Powercycle::Powercycle(const uint32_t& wakeupTime) : 
  wakeupTime_(wakeupTime) 
{
  execute();
}

void Powercycle::execute()
{   
    std::system("sh -c \"echo 0 > /sys/class/rtc/rtc0/wakealarm\"");
    std::string invokeRtc = std::string("sh -c \"echo `date '+%s' -d '+ ") + std::to_string(wakeupTime_) +" minutes'` > /sys/class/rtc/rtc0/wakealarm\"";
    std::system(invokeRtc.c_str());
    std::system("shutdown -h now");
}

