#include <iostream>
#include <cstdint>
#include "time.hpp"
#include "powercycle.hpp"
#include "util.hpp"

int main(int argc, char** argv)
{
  if (argc == 2) { /* assuming that it can never go below 1 */
    if (util::argCheck(argv)) {
      Time time(*(argv + 1));
      Powercycle powercycle(time.getWakeupTime());
    } else {
      util::handleError(Error::INVALID_ARG_TYPE);
    }   
  } else {
    util::handleError(Error::INVALID_ARG_COUNT);
  }
  return 0;
}
