#include <red_black_tree.hpp>

int main()
{
  DenseMatrix dense_matrix(5, 4);
  dense_matrix(1, 1, 9.0);
  RedBlackTree<DenseMatrix> rbt(10);
  rbt.insert(dense_matrix, 0, 0);
  // Test if root is set correctly
  std::cout << rbt.get_root().data << std::endl;
  return 0;
}