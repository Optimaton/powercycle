#include <iostream>
#include "../include/time.hpp"
#include "../include/powercycle.hpp"
#include "../include/util.hpp"

int main(int argc, char** argv)
{
	if (argc == 2) {
		/* argCheck - checks if first argument is powercycle
			 and second argument is a proper time format */
		if (util::argCheck(argv)) {
			// Time time(*(argv + 1));
			/* just set the time so that it can be used later */
			// Powercycle powercycle(time);
			/* this alarm will only go off when the time in min 
				 is more than 0 */
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
