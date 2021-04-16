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
  explicit Matrix(const std::vector<std::vector<double>> &input);
  explicit Matrix(const Tuple &input);
  Matrix(const Matrix &rhs);
  Matrix &operator=(const Matrix &rhs);

  ~Matrix();
  const std::vector<std::vector<double>> &Data();
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
  unsigned int columns() const;
  unsigned int rows() const;
  std::vector<double> &operator[](int index);
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
