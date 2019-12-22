#ifndef _matrix_h
#define _matrix_h
#include <cassert>
#include <vector>
#include "tuples.h"
#include "utils.h"

namespace ray_lib {
class Matrix {
  std::vector<std::vector<double>> _data;
  unsigned int _columns;
  unsigned int _rows;

 public:
  explicit Matrix(const std::vector<std::vector<double>> &input)
      : _data(input), _columns(input[0].size()), _rows(input.size()) {}
  explicit Matrix(const Tuple &input)
      : _columns(1), _rows(input.Values().size()) {
    for (auto a : input.Values()) {
      _data.push_back({a});
    }
  }
  const std::vector<std::vector<double>> &Data() { return _data; }
  friend bool operator==(const Matrix &lhs, const Matrix &rhs);
  friend bool operator!=(const Matrix &lhs, const Matrix &rhs);
  friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);
  friend Tuple operator*(const Matrix &lhs, const Tuple &rhs);
  friend Point operator*(const Matrix &lhs, const Point &rhs);
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
  Matrix Translate(double x, double y, double z) const;
  Matrix Scale(double x, double y, double z) const;

  Matrix Rotate_x(double radians) const;
  Matrix Rotate_y(double radians) const;
  Matrix Rotate_z(double radians) const;

  Matrix Shear(double xy, double xz, double yx, double yz, double zx,
               double zy) const;
};
const Matrix identity_4(
    {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
Matrix Translation(double x, double y, double z);
Matrix Scale(double x, double y, double z);

Matrix Rotation_x(double radians);
Matrix Rotation_y(double radians);
Matrix Rotation_z(double radians);

Matrix Shear(double xy, double xz, double yx, double yz, double zx, double zy);

}  // namespace ray_lib
#endif  //_matrix_h
