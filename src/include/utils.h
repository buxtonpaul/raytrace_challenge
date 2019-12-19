#ifndef utils_h
#define utils_h
#include <string>
#include <vector>

bool float_equals(const double &lhs, const double &rhs);
std::vector<std::string> splitlines(const std::string &in);

std::string limitlinelength(std::string in, unsigned int length);
#endif
