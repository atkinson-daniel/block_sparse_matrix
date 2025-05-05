#include <iostream>
#include "red_black_tree.hpp"
#include "block_sparse_matrix.hpp"

int main()
{
  BlockSparseMatrix bsm(4, 4);

  DenseMatrix dense_matrix1(4, 4);
  DenseMatrix dense_matrix2(4, 4);
  DenseMatrix dense_matrix3(4, 4);
  DenseMatrix dense_matrix4(4, 4);
  dense_matrix1(0, 0, 9.0);
  dense_matrix2(0, 0, 7.0);
  dense_matrix3(2, 0, 1.1);
  dense_matrix4(0, 0, 6.6);

  bsm[0, 0] = dense_matrix1;
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
