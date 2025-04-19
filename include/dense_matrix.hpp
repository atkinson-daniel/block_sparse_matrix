#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

#include <iostream>
#include <vector>

class DenseMatrix
{
public:
  int num_rows;
  int num_cols;
  std::vector<double> data;

  // initialize the amount of space required in the matrix
  DenseMatrix(int r_, int c_) : num_rows(r_), num_cols(c_), data(r_ * c_, 0.0)
  {
  }

  // TODO: refactor to be (r_idx, c_idx) = val;
  void operator()(int r_idx, int c_idx, double val)
  {
    int idx = num_cols * r_idx + c_idx;
    data[idx] = val;
  }

  // feed std::ostream protected info from Matrix
  friend std::ostream &operator<<(std::ostream &os, const DenseMatrix &matrix)
  {
    for (int i = 0; i < matrix.num_rows; ++i)
    {
      for (int j = 0; j < matrix.num_cols; ++j)
      {
        os << matrix.data[i * matrix.num_cols + j] << ' ';
      }
      os << '\n';
    }
    return os;
  };
};

#endif // DENSE_MATRIX_CPP