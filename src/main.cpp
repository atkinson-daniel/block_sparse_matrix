#include <dense_matrix.hpp>

int main()
{
  DenseMatrix dense_matrix(5, 4);
  dense_matrix(1, 1, 9.0);
  std::cout << dense_matrix << std::endl;
  return 0;
}