#include "matrix.h"
#include <algorithm>

bool operator ==(const Matrix &lhs, const Matrix &rhs)
{
   // check sizes match
  if(lhs._data.size() !=rhs._data.size())
    return false;
  
  for(int i=0; i<lhs._data.size(); ++i)
   {
     if (!std::equal(lhs._data[i].begin(), lhs._data[i].end(), rhs._data[i].begin(), rhs._data[i].end(), float_equals))
      return false;
   }
   return true;
}

bool operator !=(const Matrix &lhs, const Matrix &rhs)
{
  return (!(lhs == rhs));
}
