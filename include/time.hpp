#ifndef __TIME_H__
#define __TIME_H__

enum class Wakeup {
  IMMEDIATE = 1,
  LATER_MIN = 2,
  LATER_AT_TIME = 3,
};

enum class Separator {
  HOUR = 1,
  MIN = 2,
  SEC = 3,
};

enum class TError {
  STALE_TIME
};

/* conversion parameters */
const char SEPARATOR = ':';
const uint16_t HR_SEC = 3600;
const uint8_t MIN_SEC = 60;
const uint8_t SEC_MIN = 60;

struct Time {
 public:
  // convert given h,m,s in hh::mm::ss
  // needs an argcheck too
  explicit Time (char const* argTime);
  uint32_t getWakeupTime();
 private:
  Wakeup getWakeupType(const std::string& sArgTime);
  void setWakeupTime(uint32_t wakeupTime);
  void setImmediateTime();
  void setTimeInMinutes(const std::string& sArgTime);
  void setFormattedTime(const std::string& sArgTime);
  void convertToMinutes();
  void setHours(const uint32_t& hours);
  void setMinutes(const uint32_t& minutes);
  void setSeconds(const uint32_t& seconds);
  void handleError(const TError error);
  uint32_t hours_;
  uint32_t minutes_;
  uint32_t seconds_;
  uint32_t wakeupTime_;
};

#endif // __TIME_H__
