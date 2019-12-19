#include <iostream>
#include <fstream>
#include "tuples.h"
#include "canvas.h"
#include "color.h"


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
  Projectile p(Point(0, 1, 0), Vector(1, 1.8, 0).normalise()*11.25);
  Environment e(Vector(0, -0.1, 0) , Vector(-0.01, 0, 0));

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
