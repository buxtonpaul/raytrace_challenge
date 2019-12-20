#ifndef utils_h
#define utils_h
#include <string>
#include <vector>

bool float_equals(const double &lhs, const double &rhs);
std::vector<std::string> splitlines(const std::string &in);

std::string limitlinelength(std::string in, unsigned int length);
double vector_product(const std::vector<double> &a, const std::vector<double> &b);

std::vector<double> operator +(const std::vector<double> &a, const std::vector<double> &b);
std::vector<double> operator *(const std::vector<double> &a, const std::vector<double> &b);
std::vector<double> operator *(const double a, const std::vector<double> &b);
std::vector<double> operator *(const std::vector<double> &b, const double a);
std::vector<double> operator -(const std::vector<double> &a, const std::vector<double> &b);
std::vector<double> operator -(const std::vector<double> &a);

#endif
