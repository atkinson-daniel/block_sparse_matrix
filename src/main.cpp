#include <iostream>
#include "red_black_tree.hpp"
#include "block_sparse_matrix.hpp"

int main()
{
  BlockSparseMatrix bsm(2, 2, 4, 4);

  DenseMatrix dense_matrix1(4, 4);
  DenseMatrix dense_matrix2(4, 4);
  DenseMatrix dense_matrix3(4, 4);
  DenseMatrix dense_matrix4(4, 4);

  dense_matrix1(0, 0, 1);
  dense_matrix1(1, 1, 1);
  dense_matrix1(2, 2, 1);
  dense_matrix1(3, 3, 1);
  dense_matrix1(0, 1, 1);

  dense_matrix2(0, 0, 2);
  dense_matrix2(1, 1, 2);
  dense_matrix2(2, 2, 2);
  dense_matrix2(3, 3, 2);
  dense_matrix2(0, 1, 2);

  dense_matrix3(0, 0, 3);
  dense_matrix3(1, 1, 3);
  dense_matrix3(2, 2, 3);
  dense_matrix3(3, 3, 3);
  dense_matrix3(0, 1, 3);

  dense_matrix4(0, 0, 4);
  dense_matrix4(1, 1, 4);
  dense_matrix4(2, 2, 4);
  dense_matrix4(3, 3, 4);
  dense_matrix4(0, 1, 4);

  bsm[0, 0] = dense_matrix1;
  bsm[1, 1] = dense_matrix2;
  bsm[1, 0] = dense_matrix3;
  bsm[0, 1] = dense_matrix4;

  std::cout << bsm << std::endl;

  bsm.print_tree();

  bsm.erase(1, 0);
  std::cout << bsm << std::endl;

  bsm.print_tree();

  return 0;
}
