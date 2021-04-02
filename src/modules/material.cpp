#include "material.h"
#include <iostream>

namespace ray_lib
{
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

  ray_lib::mat_params default_matparams{.ambient = 0.1,
                                        .diffuse = 0.9,
                                        .specular = 0.9,
                                        .shiny = 200,
                                        .reflect = 0,
                                        .transparency = 0,
                                        .index = 1};

} // namespace ray_lib
