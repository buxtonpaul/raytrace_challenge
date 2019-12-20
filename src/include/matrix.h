#ifndef _matrix_h
#define _matrix_h
#include <vector>
#include "utils.h"
class Matrix{
  std::vector<std::vector <double>> _data;
  public:
  explicit Matrix(const std::vector<std::vector <double>> &input) :_data(input){}
  const std::vector<std::vector <double>> &Data (){return _data;}
  friend bool operator ==(const Matrix &lhs, const Matrix &rhs);
  friend bool operator !=(const Matrix &lhs, const Matrix &rhs);
};

#endif //_matrix_h
