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

bool arraycomparator(const std::valarray<double> & lhs, const std::valarray<double> & rhs);


tuple Vector(double x, double y, double z);
tuple Point(double x, double y, double z);

// Operators
tuple  operator *(const double &lhs, const tuple &rhs);
tuple  operator /(const tuple  &lhs, const double &rhs);

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

  tuple  operator +(const tuple &obj )const { return tuple(_vals + obj._vals);}
  tuple  operator -(const tuple &obj )const { return tuple(_vals - obj._vals);}
  tuple  operator *(const double &obj)const  { return tuple(_vals * obj);}
  tuple  operator -()const { return (tuple( - _vals));}
  bool operator ==(const tuple &obj)const { return (std::equal(begin(_vals), end(_vals),
                                            begin(obj._vals), end(obj._vals), float_equals));}
  bool operator !=(const tuple &obj)const { return !(std::equal(begin(_vals), end(_vals),
                                            begin(obj._vals), end(obj._vals), float_equals));}
  friend std::ostream & operator << (std::ostream &out, const tuple &c);

  double x() const {return _vals[0];}
  double y() const {return _vals[1];}
  double z() const {return _vals[2];}
  double w() const {return _vals[3];}
  const std::valarray <double> &Values()const {return (_vals);}
  
};


}//namespace ray_lib
#endif
