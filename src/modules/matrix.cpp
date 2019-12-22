#include "matrix.h"
#include <algorithm>
#include <iostream>
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
  vector<vector<double>> res(lhs.rows(), vector<double>(rhs.columns()));
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
  vector<vector<double>> tuplevals(rhs.size(), vector<double>(1));
  for (unsigned int i = 0; i < rhs.size(); ++i)
  {
    tuplevals[i] = {rhs.Values()[i]};
  }
  Matrix tuplematrix(tuplevals);
  return (Tuple((lhs * tuplematrix).col(0)));
}

vector<double> Matrix::row(int rownum) const
{
  return (_data[rownum]);
}

vector<double> Matrix::col(int colnum) const
{
  vector<double> res;
  for (const std::vector<double> &rows : _data)
  {
    res.push_back(rows[colnum]);
  }
  return res;
}

Matrix Matrix::transpose() const
{
  vector<vector<double>> tmp(_columns, vector<double>(_rows));
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
  if ((_rows == 2) && (_columns == 2))
    return ((_data[0][0] * _data[1][1]) - (_data[0][1] * _data[1][0]));
  double sum = 0;
  for (unsigned int i = 0; i < _columns; ++i)
  {
    sum += _data[0][i] * cofactor(0, i);
  }
  return sum;
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

/**
 * @brief Creates a submatrix which is 1 element less in each direction
 * 
 * @param remove_row Row to remove
 * @param remove_column Column to remove
 * @return Matrix 
 */
Matrix Matrix::submatrix(unsigned int remove_row, unsigned int remove_column) const
{
  // we want toreturn a matrix which has had a row and column removed
  // we could either create one full size and then use the erase function,
  // but that will be inefficient, better to create the structure the size we need
  // and populate it properly.
  unsigned int in_i = 0;
  unsigned int in_j = 0;
  vector<vector<double>> result(_rows - 1, vector<double>(_columns - 1));
  for (unsigned int i = 0; i < _rows - 1; ++i)
  {
    in_i = ((in_i == remove_row) ? (in_i + 1) : in_i);
    in_j = 0;
    for (unsigned int j = 0; j < _columns - 1; ++j)
    {
      in_j = ((in_j == remove_column) ? (in_j + 1) : in_j);
      result[i][j] = _data[in_i][in_j];
      in_j++;
    }
    in_i++;
  }
  return Matrix(result);
}

double Matrix::get_minor(unsigned int row, unsigned int column) const
{
  return submatrix(row, column).determinant();
}

double Matrix::cofactor(unsigned int row, unsigned int column) const
{
  double minorval = get_minor(row, column);
  return ((row + column & 1) == 1) ? -minorval : minorval;
}
bool Matrix::invertable() const
{
  return determinant() != 0;
}

Matrix Matrix::inverse() const
{
  // for each elment row,colum
  // == cofactor (column,row)/determinant
  vector<vector<double>> res(_columns, vector<double>(_rows));
  double d = determinant();
  for (unsigned int i = 0; i < _rows; ++i)
  {
    for (unsigned int j = 0; j < _columns; ++j)
    {
      res[i][j] = cofactor(j, i) / d;
    }
  }
  return Matrix(res);
}

} //namespace ray_lib
