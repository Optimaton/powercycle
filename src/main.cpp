#include <iostream>
#include "time.hpp"
#include "powercycle.hpp"
#include "util.hpp"

int main(int argc, char** argv)
{
  if (argc == 2) { /* assuming that it can never go below 1 */
    if (util::argCheck(argv)) {
      Time time(*(argv + 1));
      time.getTime();
      // Powercycle powercycle(time);
      /* switch (powercycle.getWakeupMode()) {
        case Wakeup.IMMEDIATE: powercycle.reboot(); break;
        case Wakeup.LATER: powercycle.setAlarm(); break;  
        default: util::handleError(Error::UNSPECIFIED_POWERCYCLE_MODE); break;
      } */
    } else {
      util::handleError(Error::INVALID_ARG_TYPE);
      util::callUsage();
    }   
  } else {
    util::handleError(Error::INVALID_ARG_COUNT);
    util::callUsage();
  }
  return 0;
}
