#ifndef __TIME_H__
#define __TIME_H__

/* TODO(raghu): populate the hh::mm::ss 
   data immediately for both system time
   and user provided time */
struct Minutes {
 public:
  explicit Minutes(int minutes);
  void setMinutes(int minutes);
  Minutes getMinutes();
 private:
  int minutes_;
};

struct Seconds {
 public:
  explicit Seconds(int seconds);
  void setSeconds(int seconds);
  Seconds getSeconds();
 private:
  int seconds_;
};

struct Hours {
 public:
  explicit Hours(int hours);
  void setHours(int hours);
  Hours getHours();
 private:
  int hours_;
};

struct Time {
 public:
  // convert given h,m,s in hh::mm::ss
  // needs an argcheck too
  explicit Time (
                const Hours& hours,
                const Minutes& minutes,
                const Seconds& seconds
                );
  void setTime(
              const Hours& hours,
              const Minutes& minutes,
              const Seconds& seconds
              );
  Time getTime();
 private:
  Hours hours_;
  Minutes minutes_;
  Seconds seconds_;
};

#endif // __TIME_H__
