#include "material.h"
#include <iostream>

namespace ray_lib {
std::ostream &operator<<(std::ostream &out, const Material &m) {
  out << "( ";
  out << "Color = " << m._color << std::endl;
  out << "Ambient = " << m._ambient << std::endl;
  out << "Diffuse = " << m._diffuse << std::endl;
  out << "Specular= " << m._specular << std::endl;
  out << "Shininess" << m._shininess << " )" << std::endl;
  return out;
}
}  // namespace ray_lib
