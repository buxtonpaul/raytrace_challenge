#ifndef tuples_h
#define tuples_h

#include <valarray>
#include <functional>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cmath>
#include "utils.h"


namespace ray_lib{
class tuple;

// A class to represent 4 element tuples used for ray tracing
// these are represented using 4 elements x,y,z,w
// where w==0 means it is a vector and w==1 means it is a point
// non class helpers
bool comparator(const double & left, const double & right);

bool arraycomparator(const std::array<double, 4> & lhs, const std::array<double, 4> & rhs);


bool  operator ==(const tuple &lhs, const tuple &rhs);
bool  operator !=(const tuple &lhs, const tuple &rhs);

tuple Vector(double x, double y, double z);
tuple Point(double x, double y, double z);

// Operators
tuple  operator +(const tuple &lhs, const tuple &rhs);
tuple  operator -(const tuple &lhs, const tuple &rhs);

tuple  operator *(const double &lhs, const tuple &rhs);
tuple  operator *(const tuple  &lhs, const double &rhs);
tuple  operator /(const tuple  &lhs, const double &rhs);
tuple  operator -(const tuple &rhs);

class tuple{
  private:
  std::valarray <double> _vals;

  public:
  explicit tuple(std::valarray<double> a): _vals(a) {}
  tuple(const tuple &r) : _vals(r._vals){}
  bool isPoint(){return float_equals(_vals[3], 1.0);}
  bool isVector(){return !isPoint();}
  double magnitude(){
    return sqrt(_vals[0] * _vals[0] +
                _vals[1] * _vals[1] +
                _vals[2] * _vals[2] +
                _vals[3] * _vals[3]);
  }

  tuple normalise(){ return ( *this / this->magnitude()) ;}
  double dotproduct(const tuple &r)const;
  tuple crossproduct(const tuple &r)const;


  static tuple arrayadder(const tuple & lhs, const tuple & rhs){
    return tuple({lhs.Values()[0] +rhs.Values()[0],
                    lhs.Values()[1] +rhs.Values()[1],
                    lhs.Values()[2] +rhs.Values()[2],
                    lhs.Values()[3] +rhs.Values()[3]});
  }
  static  tuple arraysub(const tuple & lhs, const tuple & rhs){
    return tuple({lhs.Values()[0] -rhs.Values()[0],
                    lhs.Values()[1] -rhs.Values()[1],
                    lhs.Values()[2] -rhs.Values()[2],
                    lhs.Values()[3] -rhs.Values()[3]});
  }
    static     tuple arraymul(const double & lhs, const tuple & rhs){
    return tuple({lhs * rhs.Values()[0],
                    lhs * rhs.Values()[1],
                    lhs * rhs.Values()[2],
                    lhs * rhs.Values()[3]});
  }

  double x() const {return _vals[0];}
  double y() const {return _vals[1];}
  double z() const {return _vals[2];}
  double w() const {return _vals[3];}
  const std::valarray <double> &Values()const {return (_vals);}

};


std::ostream & operator << (std::ostream &out, const tuple &c);
}
#endif
