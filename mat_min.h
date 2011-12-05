#ifndef IGL_MAT_MIN_H
#define IGL_MAT_MIN_H
#include <Eigen/Dense>

namespace igl
{
  // Ideally this becomes a super overloaded function supporting everything
  // that matlab's min supports

  // Min function for matrices to act like matlab's min function. Specifically
  // like [Y,I] = min(X,[],dim);
  //
  // Templates:
  //   T  should be a eigen matrix primitive type like int or double
  // Inputs:
  //   X  m by n matrix
  //   dim  dimension along which to take min 
  // Outputs:
  //   Y  n-long sparse vector (if dim == 1) 
  //   or
  //   Y  m-long sparse vector (if dim == 2)
  //   I  vector the same size as Y containing the indices along dim of minimum
  //     entries
  //
  // See also: mat_max
  template <typename T>
  inline void mat_min(
    const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> & X,
    const int dim,
    Eigen::Matrix<T,Eigen::Dynamic,1> & Y,
    Eigen::Matrix<int,Eigen::Dynamic,1> & I);
}

#include "verbose.h"

template <typename T>
inline void igl::mat_min(
  const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> & X,
  const int dim,
  Eigen::Matrix<T,Eigen::Dynamic,1> & Y,
  Eigen::Matrix<int,Eigen::Dynamic,1> & I)
{
  assert(dim==1||dim==2);

  // output size
  int n = (dim==1?X.cols():X.rows());
  // resize output
  Y.resize(n);
  I.resize(n);

  // loop over dimension opposite of dim
  for(int j = 0;j<n;j++)
  {
    typename Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>::Index PHONY;
    typename Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>::Index i;
    T m;
    if(dim==1)
    {
      m = X.col(j).minCoeff(&i,&PHONY);
    }else
    {
      m = X.row(j).minCoeff(&PHONY,&i);
    }
    Y(j) = m;
    I(j) = i;
  }
}

#endif
