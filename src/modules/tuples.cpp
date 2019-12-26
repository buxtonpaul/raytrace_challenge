#include "tuples.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "utils.h"

namespace ray_lib {
double Vector::dotproduct(const Vector &r) const {
  double sum = 0;
  for (unsigned int i = 0; i < this->Values().size(); ++i)
    sum += (this->Values()[i] * r.Values()[i]);
  return sum;
}

Vector Vector::crossproduct(const Vector &r) const {
  return Vector(this->y() * r.z() - this->z() * r.y(),
                this->z() * r.x() - this->x() * r.z(),
                this->x() * r.y() - this->y() * r.x());
}

double Tuple::magnitude() const {
  return sqrt(_vals[0] * _vals[0] + _vals[1] * _vals[1] + _vals[2] * _vals[2] +
              _vals[3] * _vals[3]);
}

Vector Vector::reflect(const Vector &n) const {
  Vector a = *this - n * 2 * dotproduct(n);
  return a;
}
}  // namespace ray_lib
