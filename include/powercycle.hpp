#ifndef __POWERCYCLE_H__
#define __POWERCYCLE_H__

struct Powercycle {
 public:
  explicit Powercycle(const uint32_t& wakeupTime);
 private:
  void execute();
  uint32_t wakeupTime_;
}; 

#endif // __POWERCYCLE_H__

