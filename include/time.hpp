#ifndef __TIME_H__
#define __TIME_H__

enum class Wakeup {
  IMMEDIATE = 1,
  LATER_MIN = 2,
  LATER_AT_TIME = 3,
};

const char SEPARATOR = ':';
struct Time {
 public:
  // convert given h,m,s in hh::mm::ss
  // needs an argcheck too
  explicit Time (char const* argTime, Wakeup Type);
  uint32_t getTime();
 private:
  void setHours(const uint32_t& hours);
  void setMinutes(const uint32_t& minutes);
  void setSeconds(const uint32_t& seconds);
  uint32_t hours_;
  uint32_t minutes_;
  uint32_t seconds_;
};

#endif // __TIME_H__
