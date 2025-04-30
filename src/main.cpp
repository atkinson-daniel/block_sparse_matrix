#include <red_black_tree.hpp>

int main()
{
  DenseMatrix dense_matrix(5, 4);
  dense_matrix(1, 1, 9.0);
  RedBlackTree<DenseMatrix> rbt;
  rbt.insert(dense_matrix);
  // Test if root is set correctly
  std::cout << rbt.get_root().data << std::endl;
  return 0;
}