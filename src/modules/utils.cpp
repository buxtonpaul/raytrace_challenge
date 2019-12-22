#include "utils.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#define min(a, b) ((a) > (b) ? (b) : (a))

bool float_equals(const double &lhs, const double &rhs) {
  // double margin = (min(fabs(lhs), fabs(rhs))) * 0.001;
  double margin = 0.001;
  // set the margin to be .1 % of the smallest number
  // when <0 we need to handle things differently!
  if (fabs(lhs - rhs) <= margin) return true;
  return false;
}

std::vector<std::string> splitlines(const std::string &in) {
  std::vector<std::string> a;
  std::istringstream stream(in);
  std::string line;
  while (std::getline(stream, line)) {
    a.push_back(line);
  }
  return a;
}

std::string limitlinelength(std::string in, unsigned int length) {
  std::string unprocessed = in;
  std::string processed = in;
  int lastspace = -1;
  unsigned int curpos = 0;
  for (int i = 0; i < in.length(); ++i, ++curpos) {
    if (unprocessed[i] == ' ') lastspace = i;
    if (curpos >= length) {
      if (lastspace > 0) {
        processed[lastspace] = '\n';
        curpos = i - lastspace;
        lastspace = -1;
      }
    }
  }
  return processed;
}

double vector_product(const std::vector<double> &a,
                      const std::vector<double> &b) {
  double sum = 0;

  assert(a.size() == b.size());
  for (unsigned int i = 0; i < a.size(); ++i) {
    sum += a[i] * b[i];
  }
  return sum;
}

std::string genfilestring() {
  char tmpstrinf[255];
  time_t now = time(0);
  tm *ltm = localtime(&now);
  snprintf(tmpstrinf, sizeof(tmpstrinf), "%d%02d%02d%02d%02d%02d",
           (1900 + ltm->tm_year), (1 + ltm->tm_mon), (ltm->tm_mday),
           (1 + ltm->tm_hour), (1 + ltm->tm_min), (1 + ltm->tm_sec));
  return std::string(tmpstrinf);
}