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
  dense_matrix2(0, 0, 2);
  dense_matrix3(2, 0, 3);
  dense_matrix4(0, 0, 4);

  bsm[0, 0] = dense_matrix1;
  bsm[1, 1] = dense_matrix2;
  bsm[1, 0] = dense_matrix3;
  bsm[0, 1] = dense_matrix4;
  std::cout << bsm << std::endl;

  /*
    RedBlackTree<DenseMatrix> rbt(10);
    rbt.insert(dense_matrix1, 0, 0);
    rbt.insert(dense_matrix2, 1, 0);
    rbt.insert(dense_matrix3, 2, 0);
    rbt.insert(dense_matrix4, 1, 1);

    std::cout << rbt.size() << std::endl;
    rbt.print_tree();

    rbt.remove(2, 0);
    std::cout << rbt.size() << std::endl;

    rbt.print_tree();
  */

  return 0;
}
