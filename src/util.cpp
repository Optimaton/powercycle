#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstring>
#include "util.hpp"

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

/* check second argument for now/time(in min)/hh:mm:ss */
bool argCheckOpt(const char* argOpt)
{
  bool argOptStatus = false;
  if (strcmp(argOpt,"now") == 0) {
    argOptStatus = true;
  } else {
    std::string sArgOpt(argOpt);
    for (auto& opt : sArgOpt) {
      if (!isdigit(opt))
        /* since minutes failed. check time format */
        return argCheckTime(sArgOpt);
    }
    argOptStatus = true;
  }
  
  return argOptStatus;
}


/* check second argument for time format */
bool argCheckTime(const std::string& argTime)
{
  bool argTimeStatus = false;
  const char SEPARATOR = ':';
  size_t separatorCount = 0;
  std::string timeItem;
  uint32_t hoursItem;
  uint32_t minutesItem;
  uint32_t secondsItem;
  std::stringstream splitStream(argTime);
  
  while (std::getline(splitStream, timeItem, SEPARATOR)) {
    separatorCount++;
    if (timeItem.length() != 2) /* h,m,s cannot go beyond 2 digits or be empty */
      return argTimeStatus;
    for (auto& item : timeItem) {
      if (!isdigit(item)) { /* check to ensure that time format comprises of numbers */
        return argTimeStatus;
      }
    }

    /* if we come here it means, timeItem is made of digits */
    uint32_t currentTimeItem = std::stoi(timeItem);
    if (separatorCount == 1)  { /* hours */
      hoursItem = currentTimeItem;
    }
    else if (separatorCount == 2) {/* minutes*/
      minutesItem = currentTimeItem;
    }
    else {  /* seconds */ 
      secondsItem = currentTimeItem;
    } 
      
  }

  if (hoursItem < 0 || hoursItem > 24) /* check hours */
        return argTimeStatus;

  if (hoursItem >= 0 && hoursItem < 24) { /* check minutes and seconds */
    if (minutesItem < 0 || minutesItem > 59)
      return argTimeStatus;
    if (secondsItem < 0 || secondsItem > 59)
      return argTimeStatus;
  } 
  else if (hoursItem == 24) { /* special condn when 24:_:_ */
    if (minutesItem != 0 || secondsItem != 0) 
      return argTimeStatus;
  }

  /* set true only if the format is correct */
  if (separatorCount == 3)  /* check to ensure that there are 2 colons */
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
  std::cout << "Usage: "
            << "powercycle [hh::mm::ss | minutes | now]" << std::endl;
}
}
