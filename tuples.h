#include <array>
#include <cmath>
#include <functional>
#include <algorithm>
#include <limits>
static double EPSILON = std::numeric_limits<double>::epsilon();

// A class to represent 4 element tuples used for ray tracing
// these are represented using 4 elements x,y,z,w
// where w==0 means it is a vector and w==1 means it is a point

bool comparator(const double & left, const double & right){
                    // Lambda function to compare 2 strings in case insensitive manner
                    return  fabs(left - right) < EPSILON;
                  }

bool arraycomparator(const std::array<double, 4> & lhs, const std::array<double, 4> & rhs){
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), comparator);
}

class Raytuple{
  public:
  Raytuple(const double x, const double y, const double z, const double w): _vals({x, y, z, w}) {}
  Raytuple(const Raytuple &r) : _vals(r._vals){}
  bool isPoint(){return comparator(_vals[3], 1.0);}
  bool isVector(){return !isPoint();}
  double magnitude(){
    return sqrt(_vals[0] * _vals[0] +
                _vals[1] * _vals[1] +
                _vals[2] * _vals[2] +
                _vals[3] * _vals[3]);
  }





  static Raytuple arrayadder(const Raytuple & lhs, const Raytuple & rhs){
    return Raytuple(lhs.Values()[0] +rhs.Values()[0],
                    lhs.Values()[1] +rhs.Values()[1],
                    lhs.Values()[2] +rhs.Values()[2],
                    lhs.Values()[3] +rhs.Values()[3]);
  }
     static  Raytuple arraysub(const Raytuple & lhs, const Raytuple & rhs){
    return Raytuple(lhs.Values()[0] -rhs.Values()[0],
                    lhs.Values()[1] -rhs.Values()[1],
                    lhs.Values()[2] -rhs.Values()[2],
                    lhs.Values()[3] -rhs.Values()[3]);
  }
    static     Raytuple arraymul(const double & lhs, const Raytuple & rhs){
    return Raytuple(lhs * rhs.Values()[0],
                    lhs * rhs.Values()[1],
                    lhs * rhs.Values()[2],
                    lhs * rhs.Values()[3]);
  }

  double x() {return _vals[0];}
  double y() {return _vals[1];}
  double z() {return _vals[2];}
  double w() {return _vals[3];}
  const std::array <double, 4> &Values()const {return (_vals);}

  private:
  const std::array <double, 4> _vals;
};

bool   operator ==( const Raytuple &lhs, const Raytuple &rhs)   {return arraycomparator(lhs.Values(),  rhs.Values()); }
bool  operator !=( const Raytuple &lhs, const Raytuple &rhs)   {return !(arraycomparator(lhs.Values(),  rhs.Values())); }

Raytuple Vector(double x, double y, double z) {return Raytuple(x, y, z, 0.0);}
Raytuple Point(double x, double y, double z) {return Raytuple(x, y, z, 1.0);}

Raytuple  operator +(const Raytuple &lhs, const Raytuple &rhs) { return Raytuple::arrayadder(lhs, rhs);}
Raytuple  operator -(const Raytuple &lhs, const Raytuple &rhs) { return Raytuple::arraysub(lhs, rhs);}

Raytuple  operator *(const double &lhs, const Raytuple &rhs) { return Raytuple::arraymul(lhs, rhs);}
Raytuple  operator *(const Raytuple  &lhs, const double &rhs) { return Raytuple::arraymul(rhs, lhs);}
Raytuple  operator /(const Raytuple  &lhs, const double &rhs) { return Raytuple::arraymul(1.0 / rhs, lhs);}
Raytuple  operator -(const Raytuple &rhs) { return (Raytuple(0, 0, 0, 0) - rhs);}


