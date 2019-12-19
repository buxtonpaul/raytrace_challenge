#include <iostream>
#include "tuples.h"


class Environment{
  Raytuple _gravity;
  Raytuple _wind;
  public:
  Environment(const Raytuple & gravity, const Raytuple &wind) : _gravity(gravity), _wind(wind){}
  Raytuple wind(){return _wind;}
  Raytuple gravity(){return _gravity;}
};

class Projectile
{
  private:
  Raytuple _position;
  Raytuple _velocity;

  public:
  // Projectile(const Projectile & lhs): _position(lhs._position), _velocity(lhs._velocity){}
  Projectile(const Raytuple &pos, const Raytuple &vel) : _position(pos) , _velocity(vel){}
  Raytuple Position()const {return _position;}
  Raytuple Velocity()const {return _velocity;}
};

Projectile tick(Environment envinroment, Projectile proj){
  Raytuple pos = proj.Position() + proj.Velocity();
  Raytuple velocity = proj.Velocity() + envinroment.gravity() + envinroment.wind();
  return Projectile(pos, velocity);
}

int main(int argc, char* argv[])
{
  Projectile p(Point(0, 1, 0), Vector(1, 1, 0).normalise());
  Environment e(Vector(0, -0.1, 0) , Vector(-0.01, 0, 0));

  while (p.Position().y() > 0.0)
  {
    p = tick(e, p);
  }
}
