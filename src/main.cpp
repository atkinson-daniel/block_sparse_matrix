#include <iostream>
#include <functional>
#include <random>
#include "red_black_tree.hpp"
#include "block_sparse_matrix.hpp"

int main()
{
  BlockSparseMatrix bsm(5, 5, 3, 3);
  std::vector<std::reference_wrapper<DenseMatrix>> d_matrices = {
      bsm[0, 0],
      bsm[0, 1],
      bsm[0, 2],
      bsm[1, 0],
      bsm[1, 1],
      bsm[1, 2],
      bsm[2, 3],
      bsm[2, 4],
      bsm[3, 1],
      bsm[4, 2]};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> idx(0, 3);
  std::uniform_real_distribution<> val(0, 10);

  for (int i = 0; i < 10; i++)
  {
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
    d_matrices[i].get()(int(idx(gen)), int(idx(gen)), int(val(gen)));
  }

  std::cout << bsm << std::endl;

  bsm.print_tree();

  bsm.erase(1, 0);
  std::cout << bsm << std::endl;

  bsm.print_tree();

  return 0;
}
