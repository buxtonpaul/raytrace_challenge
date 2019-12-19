#include "utils.h"
#include <cmath>
#include <algorithm>
#include <iostream>

#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>

#define min(a, b)((a) > (b) ? (b) :(a))

bool float_equals(const double &lhs, const double &rhs)
{
   double margin = (min(fabs(lhs), fabs(rhs))) * 0.001;
  // set the margin to be .1 % of the smallest number
  if (fabs(lhs - rhs) <= margin)
    return true;
  return  false;
}

std::vector<std::string> splitlines(const std::string &in)
{
  std::vector<std::string> a;
  std::istringstream stream(in);
  std::string line;
  while (std::getline(stream, line)){
   a.push_back(line);
  }
  return a;
}


std::string limitlinelength(std::string in, unsigned int length)
{
  std::string unprocessed = in;
  std::string processed = in;
  int  lastspace = -1;
  unsigned int curpos = 0;
  for (int i=0; i < in.length(); ++i, ++curpos)
  {
    if (unprocessed[i] == ' ')
      lastspace = i;
    if (curpos >= length)
    {
      if (lastspace > 0)
      {
        processed[lastspace]='\n';
        curpos = i-lastspace;
        lastspace = -1;
      }
    }
  }
  return processed;
}
