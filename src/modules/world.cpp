#include "world.h"
#include <algorithm>
#include <vector>
#include "light.h"
#include "matrix.h"
#include "rays.h"
#include "shape.h"
#include "sphere.h"
namespace ray_lib
{
  std::vector<std::shared_ptr<Shape>> &WorldBase::WorldShapes() { return _shapes; }
  std::vector<Light *> &WorldBase::WorldLights() { return _lights; }

  std::vector<ray_lib::Intersection> WorldBase::WorldIntersections(
      const ray_lib::Ray &theray) const
  {
    std::vector<ray_lib::Intersection> outputs;
    for (auto s : _shapes)
    {
      auto i{s->intersects(theray)};
      if (i.size())
      {
        // we have some intersections so add them
        for (std::vector<ray_lib::Intersection>::iterator it = i.begin();
             it != i.end(); ++it)
        {
          outputs.push_back(*it);
        }
      }
    }
    std::sort(outputs.begin(), outputs.end());
    return outputs;
    // it isn't clear if these should be clipped to only those >0...
  }

  void WorldBase::InitWorld()
  {
  }

  Color WorldBase::shade_hit(const IntersectionState &precomps, int depth) const
  {
    // TODO(me): iterate over all the lights and sum the results
    Color Surface_color{ ray_lib::lighting(precomps.Object()->material(), *_lights[0],
                             precomps.OverPoint(), precomps.Eye(),
                             precomps.Normal(), *precomps.Object(), is_shadowed(precomps.OverPoint()))};

    Color Reflected_color{reflection_hit(precomps, depth)};
    Color Refracted_color{refracted_color(precomps, depth)};
    if (precomps.Object()->material().reflectivity()> 0 && precomps.Object()->material().transparency() > 0)
    {
      double reflectance = precomps.schlick();
      return Surface_color + Reflected_color *reflectance + Refracted_color * (1-reflectance);
    }

    return Surface_color + Reflected_color + Refracted_color;
  }

  Color WorldBase::refracted_color(const IntersectionState &precomps, int depth) const
  {
    if (precomps.Object()->material().transparency() == 0.0)
      return Color::Black;
    if (depth <= 0)
      return Color::Black;

    // compute if we are in total internal reflection
    double n_ratio = precomps.n1() / precomps.n2();
    double cos_i = precomps.Eye().dotproduct(precomps.Normal());
    double sin_2t = (n_ratio *n_ratio) * (1- (cos_i*cos_i));
    if (sin_2t > 1)
      return Color::Black;

    double cos_t = sqrt(1.0 - sin_2t);
    Vector sv{ precomps.Normal() * (n_ratio*cos_i-cos_t) - precomps.Eye() *n_ratio };

    Ray refracted{precomps.Under(), sv};

    return color_at(refracted, depth-1) * precomps.Object()->material().transparency();
  }

  Color WorldBase::reflection_hit(const IntersectionState &precomps, int depth) const
  {
    if (precomps.Object()->material().reflectivity() == 0.0)
      return Color::Black;
    if (depth <= 0)
      return Color::Black;
    ray_lib::Ray reflected{precomps.OverPoint(), precomps.ReflectV()};
    return color_at(reflected, depth-1) * precomps.Object()->material().reflectivity();
  }


  Color World::color_at(const Ray &theray, int depth) const
  {
    std::vector<ray_lib::Intersection> intersections{WorldIntersections(theray)};

    const Intersection *hit{ray_lib::Intersection::GetHit(intersections)};
    if (hit == nullptr)
      return Color(0, 0, 0);
    ray_lib::IntersectionState i{*hit, theray};

    return shade_hit(i, depth);
  }

  bool World::is_shadowed(const Point &p) const
  {
    Vector v{_lights[0]->position() - p};
    double distance{v.magnitude()};
    Vector direction{v.normalise()};
    Ray r{p, direction};
    std::vector<ray_lib::Intersection> intersections{WorldIntersections(r)};

    const Intersection *hit{ray_lib::Intersection::GetHit(intersections)};
    if (hit != nullptr && (hit->t() < distance))
      return true;
    return false;
  }


  void BVHWorld::InitWorld()
  {
    // convert the list of added shapes to a hittable list
    for ( auto a : _shapes)
    {
      a->addObjects(&allshapes);
    }
    _scene = std::make_shared<bvh_node>(allshapes);
  }

  Color BVHWorld::color_at(const Ray &theray, int depth) const
  {
    Intersection rec{nullptr, INFINITY};
    if (!_scene->intersects(theray, 0, INFINITY, &rec))
      return Color(0, 0, 0);

    // do we need to transform the ray at this point
    
    ray_lib::IntersectionState i{rec, theray};

    return shade_hit(i, depth);
  }

  bool BVHWorld::is_shadowed(const Point &p) const
  {
    Vector v{_lights[0]->position() - p};
    double distance{v.magnitude()};
    Vector direction{v.normalise()};
    Ray r{p, direction};

    Intersection rec{nullptr, INFINITY};
    // if (_scene->intersects(r, 0, distance, &rec))
    // {
    //   if (rec.t() < distance)
    //     return true;
    // }
    return false;
  }


} // namespace ray_lib
