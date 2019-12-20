#include "matrix.h"
#include <algorithm>
#include <iostream>
#include "tuples.h"

namespace ray_lib{
bool operator ==(const Matrix &lhs, const Matrix &rhs)
{
   // check sizes match
  if (lhs._data.size() != rhs._data.size())
    return false;
  for (int i = 0; i < lhs._data.size(); ++i)
   {
     if (!std::equal(lhs._data[i].begin(), lhs._data[i].end(), rhs._data[i].begin(), rhs._data[i].end(), float_equals))
      return false;
   }
   return true;
}

bool operator !=(const Matrix &lhs, const Matrix &rhs)
{
  return (!(lhs == rhs));
}

Matrix operator *(const Matrix &lhs, const Matrix &rhs)
{
  // for each row and column
  // the element at x,y = product row A x Col B
  // our result showld be b.columns x a.rows in dimensions
  std::vector<std::vector<double>> res(lhs._data.size(), std::vector<double>(rhs._data.size()));
  for (int rownum=0; rownum < lhs._data.size(); ++rownum)
  {
    for (int column=0; column < rhs._data[0].size(); ++column){
      res[rownum][column] = vector_product(lhs.row(rownum), rhs.col(column));
    }
  }

  return Matrix(res);
}


tuple operator *(const Matrix &lhs, const tuple &rhs)
{
  std::vector<std::vector<double>> tuplevals(rhs.Values().size(), std::vector<double>(1));
  for (unsigned int i = 0; i < rhs.Values().size() ; ++i){
    tuplevals[i]={rhs.Values()[i]};
  }
  Matrix tuplematrix(tuplevals);
  return (tuple ((lhs * tuplematrix).col(0)));
 }


std::vector<double> Matrix::row(int rownum)const
{
  return(_data[rownum]);
}
std::vector<double> Matrix::col(int colnum)const
{
  std::vector<double> res;
  for (const std::vector<double> & rows : _data){
    res.push_back(rows[colnum]);
  }
  return res;
}



std::ostream & operator << (std::ostream &out, const Matrix &v)
{
  out << "{";
  for (auto row : v._data)
  {
    for (auto item : row)
    {
      out <<" | " << item;
    }
    out << " |" <<std::endl;
  }
  return out;
}
}//namespace ray_lib
