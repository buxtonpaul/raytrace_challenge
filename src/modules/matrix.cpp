#include "matrix.h"
#include <algorithm>
#include <iostream>
#include "tuples.h"

using std::vector;
namespace ray_lib
{

  vector<double> Matrix::row(int rownum) const { return (_data[rownum]); }

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
    vector<vector<double>> tmp{_columns, vector<double>(_rows)};
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

  /**
 * @brief Creates a submatrix which is 1 element less in each direction
 *
 * @param remove_row Row to remove
 * @param remove_column Column to remove
 * @return Matrix
 */
  Matrix Matrix::submatrix(unsigned int remove_row,
                           unsigned int remove_column) const
  {
    // we want toreturn a matrix which has had a row and column removed
    // we could either create one full size and then use the erase function,
    // but that will be inefficient, better to create the structure the size we
    // need and populate it properly.
    unsigned int in_i{0};
    unsigned int in_j{0};
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
    double minorval{get_minor(row, column)};
    return ((row + column & 1) == 1) ? -minorval : minorval;
  }
  bool Matrix::invertable() const { return determinant() != 0; }

  Matrix Matrix::inverse() const
  {
    if (_calcInverse)
    {
      // for each elment row,colum
      // == cofactor (column,row)/determinant
      if (!_inverse)
        _inverse = new Matrix{Identity};

      double d{determinant()};
      for (unsigned int i = 0; i < _rows; ++i)
      {
        for (unsigned int j = 0; j < _columns; ++j)
        {
          _inverse->_data[i][j] = cofactor(j, i) / d;
        }
      }
      _calcInverse = false;
    }
    return *_inverse;
  }

  // translations , perhaps move into another function
  Matrix Matrix::translate(const double x, const double y, const double z) const
  {
    return Matrix({{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}}) *
           *this;
  }

  // translations , perhaps move into another function
  Matrix Matrix::scale(const double x, const double y, const double z) const
  {
    return Matrix({{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}}) *
           *this;
  }

  Matrix Matrix::rotate_x(const double radians) const
  {
    return Matrix({{1, 0, 0, 0},
                   {0, cos(radians), -sin(radians), 0},
                   {0, sin(radians), cos(radians), 0},
                   {0, 0, 0, 1}}) *
           *this;
  }
  Matrix Matrix::rotate_y(const double radians) const
  {
    return Matrix({{cos(radians), 0, sin(radians), 0},
                   {0, 1, 0, 0},
                   {-sin(radians), 0, cos(radians), 0},
                   {0, 0, 0, 1}}) *
           *this;
  }
  Matrix Matrix::rotate_z(const double radians) const
  {
    return Matrix({{cos(radians), -sin(radians), 0, 0},
                   {sin(radians), cos(radians), 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}}) *
           *this;
  }

  Matrix Matrix::shear(const double xy, const double xz, const double yx, const double yz, const double zx,
                       const double zy) const
  {
    return Matrix(
               {{1, xy, xz, 0}, {yx, 1, yz, 0}, {zx, zy, 1, 0}, {0, 0, 0, 1}}) *
           *this;
  }

  // translations , perhaps move into another function
  Matrix translation(const double x, const double y, const double z)
  {
    return Matrix({{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}});
  }

  // translations , perhaps move into another function
  Matrix scale(const double x, const double y, const double z)
  {
    return Matrix({{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}});
  }

  Matrix rotation_x(const double radians)
  {
    return Matrix({{1, 0, 0, 0},
                   {0, cos(radians), -sin(radians), 0},
                   {0, sin(radians), cos(radians), 0},
                   {0, 0, 0, 1}});
  }
  Matrix rotation_y(const double radians)
  {
    return Matrix({{cos(radians), 0, sin(radians), 0},
                   {0, 1, 0, 0},
                   {-sin(radians), 0, cos(radians), 0},
                   {0, 0, 0, 1}});
  }
  Matrix rotation_z(const double radians)
  {
    return Matrix({{cos(radians), -sin(radians), 0, 0},
                   {sin(radians), cos(radians), 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}});
  }

  Matrix shear(const double xy, const double xz, const double yx, const double yz, const double zx, const double zy)
  {
    return Matrix({{1, xy, xz, 0}, {yx, 1, yz, 0}, {zx, zy, 1, 0}, {0, 0, 0, 1}});
  }

  Matrix::Matrix(const std::vector<std::vector<double>> &input)
      : _data(input), _columns(input[0].size()), _rows(input.size()) {}
  Matrix::Matrix(const Tuple &input)
      : _columns(1), _rows(input.Values().size())
  {
    for (auto a : input.Values())
    {
      _data.push_back({a});
    }
    _calcInverse = true;
  }
  Matrix::Matrix(const Matrix &rhs) : _columns{rhs._columns}, _rows{rhs._rows}, _data{rhs._data}, _calcInverse{rhs._calcInverse}
  {
    if (!_calcInverse)
      _inverse = new Matrix{*rhs._inverse};
  }

  Matrix &Matrix::operator=(const Matrix &rhs)
  {
    _columns = rhs._columns;
    _rows = rhs._rows;
    _data = rhs._data;
    _calcInverse = rhs._calcInverse;
    if (!_calcInverse)
      _inverse = new Matrix{*rhs._inverse};

    return *this;
  }

  Matrix::~Matrix()
  {
    if (_inverse)
    {
      delete (_inverse);
      _inverse = nullptr;
    }
  }
  const std::vector<std::vector<double>> &Matrix::Data() { return _data; }

  unsigned int Matrix::columns() const { return _columns; }
  unsigned int Matrix::rows() const { return _rows; }
  std::vector<double> &Matrix::operator[](int index) { return _data[index]; }
  const Matrix Matrix::Identity{
      Matrix({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}})};

} // namespace ray_lib
