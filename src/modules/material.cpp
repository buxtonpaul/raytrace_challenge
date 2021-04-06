#include "material.h"
#include <iostream>

namespace ray_lib
{
  SolidPattern SolidWhite(Color::White);
  std::ostream &operator<<(std::ostream &out, const Material &m)
  {
    out << "( ";
    // out << "Color = " << m._color << std::endl;
    out << "Ambient = " << m._ambient << std::endl;
    out << "Diffuse = " << m._diffuse << std::endl;
    out << "Specular= " << m._specular << std::endl;
    out << "Reflectiveness= " << m._reflectiveness << std::endl;
    out << "Shininess" << m._shininess << " )" << std::endl;
    return out;
  }


ray_lib::Material glass = Material().Transparency(1).RefractiveIndex(1.5);


} // namespace ray_lib
