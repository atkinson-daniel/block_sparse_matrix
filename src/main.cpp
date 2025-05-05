#include <red_black_tree.hpp>

int main()
{
  DenseMatrix dense_matrix1(4, 4);
  DenseMatrix dense_matrix2(4, 4);
  DenseMatrix dense_matrix3(4, 4);
  DenseMatrix dense_matrix4(4, 4);
  dense_matrix1(1, 1, 9.0);
  dense_matrix2(0, 0, 7.0);
  dense_matrix3(2, 0, 1.1);
  dense_matrix4(0, 0, 6.6);
  RedBlackTree<DenseMatrix> rbt(10);
  rbt.insert(dense_matrix1, 0, 0);
  rbt.insert(dense_matrix2, 1, 0);
  rbt.insert(dense_matrix3, 2, 0);
  rbt.insert(dense_matrix4, 1, 1);
  // Test if root is set correctly
  std::cout << rbt.find(2, 0).data << std::endl;
  // rbt.print_tree(rbt.get_root());
  return 0;
}