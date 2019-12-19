#include <iostream>
#include <fstream>
#include "tuples.h"
#include "canvas.h"
#include "color.h"


class Environment{
  ray_lib::tuple _gravity;
  ray_lib::tuple _wind;
  public:
  Environment(const ray_lib::tuple & gravity, const ray_lib::tuple &wind) : _gravity(gravity), _wind(wind){}
  ray_lib::tuple wind(){return _wind;}
  ray_lib::tuple gravity(){return _gravity;}
};

class Projectile
{
  private:
  ray_lib::tuple _position;
  ray_lib::tuple _velocity;

  public:
  // Projectile(const Projectile & lhs): _position(lhs._position), _velocity(lhs._velocity){}
  Projectile(const ray_lib::tuple &pos, const ray_lib::tuple &vel) : _position(pos) , _velocity(vel){}
  ray_lib::tuple Position()const {return _position;}
  ray_lib::tuple Velocity()const {return _velocity;}
};

Projectile tick(Environment envinroment, Projectile proj){
  ray_lib::tuple pos = proj.Position() + proj.Velocity();
  ray_lib::tuple velocity = proj.Velocity() + envinroment.gravity() + envinroment.wind();
  return Projectile(pos, velocity);
}

int main(int argc, char* argv[])
{
  Projectile p(ray_lib::Point(0, 1, 0), ray_lib::Vector(1, 1.8, 0).normalise()*11.25);
  Environment e(ray_lib::Vector(0, -0.1, 0) , ray_lib::Vector(-0.01, 0, 0));

  Canvas c(900, 550);
  do
  {
    c.Pixel(p.Position().x(), c.height()-p.Position().y(), Color({1, 0, 0}));
    p = tick(e, p);
    std::cout << "x,y = " << p.Position().x() << ", " <<c.height()-p.Position().y() <<std::endl;
  }while (p.Position().y() >= 0.0);
  std::ofstream outfile("somefile.ppm");
  outfile<< c.ppm();
  outfile.close();
}

// int main (int argc, char *argv[])
// {
//   Canvas c(32, 32);
//   for (int i = 0; i < c.height(); ++i){
//     for (int j = 0; j < c.width(); ++j){
//       if ( i == j)
//       {
//         c.Pixel(j, i, Color({1, 0, 0}));
//       }
//     }
//   }
//   std::ofstream outfile("somefile.ppm");
//   outfile<< c.ppm();
//   outfile.close();

// }
