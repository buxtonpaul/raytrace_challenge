#include "matrix.h"
#include <algorithm>
#include <iostream>
#include "tuples.h"

namespace ray_lib
{
bool operator==(const Matrix &lhs, const Matrix &rhs)
{
  // check sizes match
  if ((lhs.rows()) != rhs.rows() || ((lhs.columns()) != rhs.columns()))
    return false;
  for (int i = 0; i < lhs.rows(); ++i)
  {
    if (!std::equal(lhs._data[i].begin(), lhs._data[i].end(), rhs._data[i].begin(), rhs._data[i].end(), float_equals))
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
  std::vector<std::vector<double>> res(lhs.rows(), std::vector<double>(rhs.columns()));
  for (int rownum = 0; rownum < lhs.rows(); ++rownum)
  {
    for (int column = 0; column < rhs.columns(); ++column)
    {
      res[rownum][column] = vector_product(lhs.row(rownum), rhs.col(column));
    }
  }

  return Matrix(res);
}

Tuple operator*(const Matrix &lhs, const Tuple &rhs)
{
  std::vector<std::vector<double>> tuplevals(rhs.size(), std::vector<double>(1));
  for (unsigned int i = 0; i < rhs.size(); ++i)
  {
    tuplevals[i] = {rhs.Values()[i]};
  }
  Matrix tuplematrix(tuplevals);
  return (Tuple((lhs * tuplematrix).col(0)));
}

std::vector<double> Matrix::row(int rownum) const
{
  return (_data[rownum]);
}
std::vector<double> Matrix::col(int colnum) const
{
  std::vector<double> res;
  for (const std::vector<double> &rows : _data)
  {
    res.push_back(rows[colnum]);
  }
  return res;
}

Matrix Matrix::transpose() const
{
  std::vector<std::vector<double>> tmp(_columns, std::vector<double>(_rows));
  for (unsigned int i = 0; i < _columns; ++i)
  {
    for (unsigned int j = 0; j < _rows; ++j)
    {
      tmp[i][j] = _data[j][i];
    }
  }
  return Matrix(tmp);
}

double Matrix::determinant() const
{
  assert((_rows == 2) && (_columns == 2));
  return ((_data[0][0] * _data[1][1]) - (_data[0][1] * _data[1][0]));
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
} //namespace ray_lib
