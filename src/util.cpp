#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstring>
#include "../include/util.hpp"

namespace util {

/* check if first arg is "powercycle"
   second arg is a proper time */
bool argCheck(char const* const* argv)
{
  bool argStatus = false;
  if (strcmp(*(argv + 0),"./powercycle") == 0 ||
			strcmp(*(argv + 0), "powercycle") == 0) {
    if (argCheckOpt(*(argv + 1))) {
      argStatus = true;
    }
  }
  return argStatus;
}

bool argCheckOpt(const char* argOpt)
{
	bool argOptStatus = false;
	if (strcmp(argOpt,"now") == 0) {
		argOptStatus = true;
	} else {
		std::string sArgOpt(argOpt);
		for (auto& opt : sArgOpt) {
			if (!isdigit(opt))
				/*	since minutes failed. check time format */
				return argCheckTime(sArgOpt);
		}
		argOptStatus = true;
	}
	
	return argOptStatus;
}


/* check second argument for time format */
bool argCheckTime(const std::string& argTime)
{
	/* TODO(raghu): add check to limit numbers in hh::mm::ss 
		 format */
  bool argTimeStatus = false;
  const char SEPARATOR = ':';
  size_t seperatorCount = 0;
  std::string timeItem;
  std::stringstream splitStream(argTime);
  while (std::getline(splitStream, timeItem, SEPARATOR)) {
    seperatorCount++;
		if (timeItem.length() > 2 || timeItem.empty()) 
			return argTimeStatus;
    for (auto& item : timeItem) {
      if (!isdigit(item)) {
        return argTimeStatus;
      }
    }
	}

  /* set true only if the format is correct */
  if (seperatorCount == 3)
    argTimeStatus = true;

  return argTimeStatus;
}

/* handle generic error */
void handleError(const Error&& err) 
{
	std::string errorMsg;
	if (err == Error::INVALID_ARG_COUNT)
		errorMsg = "Command Failed. Invalid Argument Count.";
	if (err == Error::INVALID_ARG_TYPE)
		errorMsg = "Command Failed. Invalid Argument Type.";
	if (err == Error::UNSPECIFIED_POWERCYCLE_MODE)
		errorMsg = "Command Failed. Unspecified Powercycle Mode.";
	std::cout << errorMsg << std::endl;
}

/* show appropriate usage format */
void callUsage() 
{
	std::cout << "powercycle [hh::mm::ss | minutes | now]" << std::endl;
}
}
