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
                _vals[3] * _vals[3]
);}

  template <typename L, typename R> bool friend  operator ==( const L &lhs, const R &rhs)   {return arraycomparator(lhs,  rhs); }
  template <typename L, typename R> bool friend operator !=( const L &lhs, const R &rhs)   {return !arraycomparator(lhs,  rhs); }

  template <typename L, typename R>   friend Raytuple arrayadder(const L & lhs, const R & rhs){
    return Raytuple(lhs._vals[0] +rhs._vals[0],
                    lhs._vals[1] +rhs._vals[1],
                    lhs._vals[2] +rhs._vals[2],
                    lhs._vals[3] +rhs._vals[3]);
  }
  template <typename L, typename R>   friend Raytuple arraysub(const L & lhs, const R & rhs){
    return Raytuple(lhs._vals[0] -rhs._vals[0],
                    lhs._vals[1] -rhs._vals[1],
                    lhs._vals[2] -rhs._vals[2],
                    lhs._vals[3] -rhs._vals[3]);
  }
    template <typename R>   friend Raytuple arraymul(const double & lhs, const R & rhs){
    return Raytuple(lhs * rhs._vals[0],
                    lhs * rhs._vals[1],
                    lhs * rhs._vals[2],
                    lhs * rhs._vals[3]);
  }

  Raytuple friend operator +(const Raytuple &lhs, const Raytuple &rhs) { return arrayadder(lhs, rhs);}
  Raytuple friend operator -(const Raytuple &lhs, const Raytuple &rhs) { return arraysub(lhs, rhs);}

  Raytuple friend operator *(const double &lhs, const Raytuple &rhs) { return arraymul(lhs, rhs);}
  Raytuple friend operator *(const Raytuple  &lhs, const double &rhs) { return arraymul(rhs, lhs);}
  Raytuple friend operator /(const Raytuple  &lhs, const double &rhs) { return arraymul(1.0 / rhs, lhs);}
  Raytuple friend operator -(const Raytuple &rhs) { return (Raytuple(0, 0, 0, 0) - rhs);}

  double x() {return _vals[0];}
  double y() {return _vals[1];}
  double z() {return _vals[2];}
  double w() {return _vals[3];}
  const std::array <double, 4> &Values()const {return (_vals);}

  private:
  const std::array <double, 4> _vals;
};

Raytuple Vector(double x, double y, double z) {return Raytuple(x, y, z, 0.0);}
Raytuple Point(double x, double y, double z) {return Raytuple(x, y, z, 1.0);}

template <typename L, typename R>   bool arraycomparator(const L & lhs, const R & rhs){
  auto a = lhs.Values();
  auto b = rhs.Values();
  return std::equal(a.begin(), a.end(), b.begin(), b.end(), comparator);
}

