#ifndef __UTIL_H__
#define __UTIL_H__	

enum class Error {
  INVALID_ARG_COUNT,
  INVALID_ARG_TYPE,
	UNSPECIFIED_POWERCYCLE_MODE,
};

namespace util {

bool argCheck(char const* const* argv);
bool argCheckOpt(const char* argOpt);
bool argCheckTime(const std::string& argTime);
void handleError(const Error&& err);
void callUsage();

}

#endif // __UTIL_H__
