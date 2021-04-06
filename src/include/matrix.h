#ifndef _matrix_h
#define _matrix_h
#include <cassert>
#include <vector>
#include "tuples.h"
#include "utils.h"

namespace ray_lib
{
class Matrix
{
  std::vector<std::vector<double>> _data;
  unsigned int _columns;
  unsigned int _rows;
  mutable Matrix *_inverse = nullptr;
  mutable bool _calcInverse = true;

public:
  explicit Matrix(const std::vector<std::vector<double>> &input)
      : _data(input), _columns(input[0].size()), _rows(input.size()) {}
  explicit Matrix(const Tuple &input)
      : _columns(1), _rows(input.Values().size())
  {
    for (auto a : input.Values())
    {
      _data.push_back({a});
    }
    _calcInverse = true;
  }
  Matrix(const Matrix &rhs) : _columns{rhs._columns}, _rows{rhs._rows}, _data{rhs._data}, _calcInverse{rhs._calcInverse}
  {
    if (!_calcInverse)
      _inverse = new Matrix{*rhs._inverse};
  }

  Matrix &operator=(const Matrix &rhs)
  {
    _columns = rhs._columns;
    _rows = rhs._rows;
    _data = rhs._data;
    _calcInverse = rhs._calcInverse;
    if (!_calcInverse)
      _inverse = new Matrix{*rhs._inverse};

    return *this;
  }

  ~Matrix()
  {
    if (_inverse)
    {
      delete (_inverse);
      _inverse = nullptr;
    }
  }
  const std::vector<std::vector<double>> &Data() { return _data; }
  friend bool operator==(const Matrix &lhs, const Matrix &rhs);
  friend bool operator!=(const Matrix &lhs, const Matrix &rhs);
  friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);

  template <class T>
  friend T operator*(const Matrix &lhs, const T &rhs);
  friend std::ostream &operator<<(std::ostream &out, const Matrix &v);
  std::vector<double> row(int rownum) const;
  std::vector<double> col(int colnum) const;
  Matrix transpose() const;
  double determinant() const;
  Matrix submatrix(unsigned int remove_row, unsigned int remove_column) const;
  double get_minor(unsigned int row, unsigned int column) const;
  double cofactor(unsigned int row, unsigned int column) const;
  bool invertable() const;
  Matrix inverse() const;
  unsigned int columns() const { return _columns; }
  unsigned int rows() const { return _rows; }
  std::vector<double> &operator[](int index) { return _data[index]; }
  Matrix translate(double x, double y, double z) const;
  Matrix scale(double x, double y, double z) const;

  Matrix rotate_x(double radians) const;
  Matrix rotate_y(double radians) const;
  Matrix rotate_z(double radians) const;

  Matrix shear(double xy, double xz, double yx, double yz, double zx,
                double zy) const;
  static const Matrix Identity;
};

Matrix translation(const double x, const double y, const double z);
Matrix scale(const double x, const double y, const double z);

Matrix rotation_x(const double radians);
Matrix rotation_y(const double radians);
Matrix rotation_z(const double radians);

Matrix shear(const double xy, const double xzconst, double yx, const double yz, const double zx, const double zy);

template <class T>
T operator*(const Matrix &lhs, const T &rhs)
{
  std::vector<std::vector<double>> tuplevals(rhs.size(),
                                              std::vector<double>(1));
  for (unsigned int i = 0; i < rhs.size(); ++i)
  {
    tuplevals[i] = {rhs.Values()[i]};
  }
  Matrix tuplematrix(tuplevals);
  return (T((lhs * tuplematrix).col(0)));
}

} // namespace ray_lib
#endif //_matrix_h
