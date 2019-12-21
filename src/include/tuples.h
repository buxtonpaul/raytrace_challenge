#ifndef tuples_h
#define tuples_h

#include <vector>
#include <functional>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cmath>
#include "utils.h"


namespace ray_lib{
class Tuple;

// A class to represent 4 element tuples used for ray tracing
// these are represented using 4 elements x,y,z,w
// where w==0 means it is a vector and w==1 means it is a point
// non class helpers


Tuple Vector(double x, double y, double z);
Tuple Point(double x, double y, double z);


class Tuple{
  private:
  std::vector <double> _vals;
  unsigned int _size;

  public:
  explicit Tuple(std::vector<double> a): _vals(a) , _size(a.size()){}
  Tuple(const Tuple &r) : _vals(r._vals){}
  bool isPoint(){return float_equals(_vals[3], 1.0);}
  bool isVector(){return !isPoint();}
  double magnitude(){
    return sqrt(_vals[0] * _vals[0] +
                _vals[1] * _vals[1] +
                _vals[2] * _vals[2] +
                _vals[3] * _vals[3]);
  }

  Tuple normalise(){ return ( *this / this->magnitude()) ;}
  double dotproduct(const Tuple &r)const;
  Tuple crossproduct(const Tuple &r)const;

  bool  operator ==(const Tuple &obj)const { return (std::equal(begin(_vals), end(_vals),
                                             begin(obj._vals), end(obj._vals), float_equals));}

  // Operators
  friend std::ostream & operator << (std::ostream &out, const Tuple &c);
  friend Tuple  operator *(const double &lhs, const Tuple &rhs);
  friend Tuple  operator *(const Tuple &lhs, const double &rhs);
  friend Tuple  operator *(const Tuple  &lhs, const Tuple &rhs);
  friend Tuple  operator /(const Tuple  &lhs, const double &rhs);
  friend Tuple  operator +(const Tuple  &lhs, const Tuple &rhs);
  friend Tuple  operator -(const Tuple  &lhs, const Tuple &rhs);
  friend Tuple  operator -(const Tuple &lhs);

  double x() const {return _vals[0];}
  double y() const {return _vals[1];}
  double z() const {return _vals[2];}
  double w() const {return _vals[3];}
  unsigned int size()const{return _size;}
  const std::vector <double> &Values()const {return (_vals);}
  double &operator[] (int index){return _vals[index];}
};


}//namespace ray_lib
#endif
