#ifndef _matrix_h
#define _matrix_h
#include <cassert>
#include <vector>
#include "utils.h"
#include "tuples.h"

class Matrix{
  std::vector<std::vector <double>> _data;

  public:
  explicit Matrix(const std::vector<std::vector <double>> &input) :_data(input){}
  explicit Matrix(const ray_lib::tuple &input) {
    for (auto a : input.Values())
    {
      _data.push_back({a});
    }
  }
  // operator ray_lib::tuple() {
  //   assert(_data[0].size() == 1);
  //   return (ray_lib::tuple(col(0)));
  // }
  const std::vector<std::vector <double>> &Data (){return _data;}
  friend bool operator ==(const Matrix &lhs, const Matrix &rhs);
  friend bool operator !=(const Matrix &lhs, const Matrix &rhs);
  friend Matrix operator *(const Matrix &lhs, const Matrix &rhs);
  friend ray_lib::tuple operator *(const Matrix &lhs, const ray_lib::tuple &rhs);
  friend std::ostream & operator << (std::ostream &out, const Matrix &v);
  std::vector<double> row(int rownum)const;
  std::vector<double> col(int colnum)const;
};

#endif //_matrix_h
