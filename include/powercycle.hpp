#ifndef __POWERCYCLE_H__
#define __POWERCYCLE_H__

const uint8_t SECONDS = 60;
const std::string RTC_WAKEALARM = "/sys/class/rtc/rtc0/wakealarm";

struct Powercycle {
 public:
  explicit Powercycle(const uint32_t& wakeupTime);
 private:
  void execute();
  void invokeRTC();
  void shutdown();
  uint32_t wakeupTime_;
}; 

#endif // __POWERCYCLE_H__

