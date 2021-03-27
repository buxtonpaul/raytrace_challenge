#include <algorithm>
#include <iostream>
#include "matrix.h"
#include "tuples.h"

using std::vector;
namespace ray_lib
{

  bool operator==(const Matrix &lhs, const Matrix &rhs)
  {
    // check sizes match
    if ((lhs.rows()) != rhs.rows() || ((lhs.columns()) != rhs.columns()))
      return false;
    for (int i = 0; i < lhs.rows(); ++i)
    {
      if (!std::equal(lhs._data[i].begin(), lhs._data[i].end(),
                      rhs._data[i].begin(), rhs._data[i].end(), float_equals))
        return false;
    }
    return true;
  }

  bool operator!=(const Matrix &lhs, const Matrix &rhs)
  {
    return (!(lhs == rhs));
  }

  Matrix operator*(const Matrix &lhs, const Matrix &rhs)
  {
    // for each row and column
    // the element at x,y = product row A x Col B
    // our result showld be b.columns x a.rows in dimensions
    vector<vector<double>> res{lhs.rows(), vector<double>(rhs.columns())};
    for (int rownum = 0; rownum < lhs.rows(); ++rownum)
    {
      for (int column = 0; column < rhs.columns(); ++column)
      {
        res[rownum][column] = vector_product(lhs.row(rownum), rhs.col(column));
      }
    }

    return Matrix(res);
  }

  std::ostream &operator<<(std::ostream &out, const Matrix &v)
  {
    out << "{";
    for (auto row : v._data)
    {
      for (auto item : row)
      {
        out << " | " << item;
      }
      out << " |" << std::endl;
    }
    return out;
  }

} // namespace ray_lib
