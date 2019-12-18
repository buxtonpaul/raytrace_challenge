#include "utils.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#define min(a, b)((a) > (b) ? (b) :(a))

bool float_equals(const double &lhs, const double &rhs)
{
   double margin = (min(fabs(lhs), fabs(rhs))) * 0.001;
  // set the margin to be .1 % of the smallest number
  if (fabs(lhs - rhs) <= margin)
    return true;
  return  false;
}
