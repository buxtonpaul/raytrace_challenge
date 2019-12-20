#ifndef _matrix_h
#define _matrix_h
#include <cassert>
#include <vector>
#include "utils.h"
#include "tuples.h"

namespace ray_lib{
class Matrix{
  std::vector<std::vector <double>> _data;

  public:
  explicit Matrix(const std::vector<std::vector <double>> &input) :_data(input){}
  explicit Matrix(const tuple &input) {
    for (auto a : input.Values())
    {
      _data.push_back({a});
    }
  }
  const std::vector<std::vector <double>> &Data (){return _data;}
  friend bool operator ==(const Matrix &lhs, const Matrix &rhs);
  friend bool operator !=(const Matrix &lhs, const Matrix &rhs);
  friend Matrix operator *(const Matrix &lhs, const Matrix &rhs);
  friend tuple operator *(const Matrix &lhs, const tuple &rhs);
  friend std::ostream & operator << (std::ostream &out, const Matrix &v);
  std::vector<double> row(int rownum)const;
  std::vector<double> col(int colnum)const;
  Matrix transpose()const;
  double determinant()const;
};
const Matrix identity_4({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}//namespace ray_lib
#endif //_matrix_h
