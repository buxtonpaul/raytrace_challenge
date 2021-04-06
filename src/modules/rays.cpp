#include "rays.h"
#include <vector>
#include "matrix.h"
#include "sphere.h"
#include "tuples.h"
#include "utils.h"
#include "algorithm"
namespace ray_lib
{

  std::ostream &operator<<(std::ostream &out, const Ray &r)
  {
    out << "Ray Origin :" << r._origin << " Direction " << r._direction
        << std::endl;
    return out;
  }

  std::ostream &operator<<(std::ostream &out, const Intersection &i)
  {
    out << "Intersection distance t= :" << i.t() << std::endl;
    return out;
  }

  const Intersection *Intersection::GetHit(
      const std::vector<Intersection> &intersections)
  {
    const Intersection *min{nullptr};
    for (unsigned int i = 0; i < intersections.size(); ++i)
    {
      if (intersections[i].t() > 0)
      {
        if (min != nullptr)
        {
          if (intersections[i].t() < min->t())
            min = &intersections[i];
        }
        else
        {
          min = &intersections[i];
        }
      }
    }
    return min;
  }

  void IntersectionState::computeSurfaceParams()
  {
    if (_normal.dotproduct(_eye) < 0.0) {
      _inside = true;
      _normal = -_normal;
    } else {
      _inside = false;
    }
    _overPoint = _position + _normal * (1.0 * __FLT_EPSILON__);
    _underPoint = _position - _normal * (1.0 * __FLT_EPSILON__);

  }
  void IntersectionState::computeRefractionparams(const Intersection &i) {
    std::vector<Intersection> tmp{i};
    computeRefractionparams(i, tmp);
  }

  double IntersectionState::schlick() const{
    double cos { _eye.dotproduct(_normal)};

    if (_n1 > _n2)
    {
      double n  {_n1/_n2};
      double sin2_t {n*n * (1 - cos * cos)};
      if (sin2_t > 1.0)
        return 1.0;
      double cos_t {sqrt(1-sin2_t)};
      cos = cos_t;
    }
    double rx { (_n1-_n2) / (_n1+_n2)};
    double r0 {rx*rx };
    return r0 + (1.0 - r0) * pow(1.0-cos, 5);
  }

  void IntersectionState::computeRefractionparams(const Intersection &i, const std::vector<Intersection> &intersections)
  {
    std::vector<const Shape *> containers;

    for (auto intersection : intersections){
      if (i == intersection)
      {
        if (containers.empty())
        {
          _n1 = 1.0;
        }
        else
        {
          _n1 = containers.back()->material().refractive_index();
        }
      }

      auto p = std::find(containers.begin(), containers.end(), intersection.GetShape());
      if ( p != containers.end())
      {
          containers.erase(p);
      }
      else
      {
        containers.push_back(intersection.GetShape());
      }
      if (i == intersection)
      {
        if (containers.empty())
        {
          _n2 = 1.0;
        }
        else
        {
          _n2 = containers.back()->material().refractive_index();
        }
      }
    }
  }


} // namespace ray_lib
