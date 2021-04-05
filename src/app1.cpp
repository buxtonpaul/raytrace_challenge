#include <fstream>
#include <iostream>
#include "canvas.h"
#include "color.h"
#include "tuples.h"

using namespace ray_lib;
class Environment
{
  Vector _gravity;
  Vector _wind;

public:
  Environment(const Vector &gravity, const Vector &wind)
      : _gravity(gravity), _wind(wind) {}
  Vector wind() { return _wind; }
  Vector gravity() { return _gravity; }
};

class Projectile
{
private:
  Point _position;
  Vector _velocity;

public:
  // Projectile(const Projectile & lhs): _position(lhs._position),
  // _velocity(lhs._velocity){}
  Projectile(const Point &pos, const Vector &vel)
      : _position(pos), _velocity(vel) {}
  Point Position() const { return _position; }
  Vector Velocity() const { return _velocity; }
};

Projectile tick(Environment envinroment, Projectile proj)
{
  Point pos = proj.Position() + proj.Velocity();
  Vector velocity{
      proj.Velocity() + envinroment.gravity() + envinroment.wind()};
  return Projectile(pos, velocity);
}

int main(int argc, char *argv[])
{
  Projectile p{Point(0, 1, 0),
               Vector(1, 1.8, 0).normalise() * 11.25};
  Environment e{Vector(0, -0.1, 0), Vector(-0.01, 0, 0)};

  Canvas c{900, 550};
  do
  {
    c.Pixel(p.Position().x(), c.height() - p.Position().y(), Color(1, 0, 0));
    p = tick(e, p);
    std::cout << "x,y = " << p.Position().x() << ", "
              << c.height() - p.Position().y() << std::endl;
  } while (p.Position().y() >= 0.0);
  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << c.ppm();
  outfile.close();
}
