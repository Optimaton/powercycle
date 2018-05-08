#ifndef __POWERCYCLE_H__
#define __POWERCYCLE_H__

struct Powercycle {
 public:
  /* convert into minutes and use it as rtc
   * takes in only minutes 
   */
  explicit Powercycle(const Time& time);
  void setAlarm();
 private:
  Time wakeupTime_;
  // Minutes wakeupMinutes_;
}; 

#endif // __POWERCYCLE_H__

