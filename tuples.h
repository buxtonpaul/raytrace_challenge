#include <array>
#include <cmath>
#include <functional>
#include <algorithm>
#include <limits>
#include <iostream>
// epsilon value way too small when we start doing divide by sqrt magnitude...
static double EPSILON = 0.0001;//std::numeric_limits<double>::epsilon();

class Raytuple;

// A class to represent 4 element tuples used for ray tracing
// these are represented using 4 elements x,y,z,w
// where w==0 means it is a vector and w==1 means it is a point
// non class helpers
bool comparator(const double & left, const double & right);

bool arraycomparator(const std::array<double, 4> & lhs, const std::array<double, 4> & rhs);


bool   operator ==(const Raytuple &lhs, const Raytuple &rhs);
bool  operator !=(const Raytuple &lhs, const Raytuple &rhs);

Raytuple Vector(double x, double y, double z);
Raytuple Point(double x, double y, double z);

// Operators
Raytuple  operator +(const Raytuple &lhs, const Raytuple &rhs);
Raytuple  operator -(const Raytuple &lhs, const Raytuple &rhs);

Raytuple  operator *(const double &lhs, const Raytuple &rhs);
Raytuple  operator *(const Raytuple  &lhs, const double &rhs);
Raytuple  operator /(const Raytuple  &lhs, const double &rhs);
Raytuple  operator -(const Raytuple &rhs);

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


  Raytuple normalise(){ return ( *this / this->magnitude()) ;}
  double dotproduct(const Raytuple &r){ return 0;}


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


std::ostream & operator << (std::ostream &out, const Raytuple &c);


