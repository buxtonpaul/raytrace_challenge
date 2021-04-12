#ifndef utils_h
#define utils_h
#include <algorithm>
#include <string>
#include <vector>

bool float_equals(const double &lhs, const double &rhs);
std::vector<std::string> splitlines(const std::string &in);
std::string limitlinelength(std::string in, unsigned int length);
double vector_product(const std::vector<double> &a,
                      const std::vector<double> &b);
std::string genfilestring();

template <typename t>
bool contains(std::vector<t> container, t data) {
  if (std::find(container.begin(), container.end(), data) == container.end())
    return false;
  return true;
}
std::pair<double, double> check_axis(double origin, double direction);
#endif
