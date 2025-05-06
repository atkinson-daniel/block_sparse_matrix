#include <iostream>
#include <functional>
#include <random>
#include "red_black_tree.hpp"
#include "block_sparse_matrix.hpp"

int main()
{
  BlockSparseMatrix bsm(5, 5, 3, 3);
  std::vector<std::reference_wrapper<DenseMatrix>> d_matrices = {
      bsm[0, 0],  // key = 0
      bsm[0, 1],  // key = 1
      bsm[0, 2],  // key = 2
      bsm[1, 0],  // key = 5
      bsm[1, 1],  // key = 6
      bsm[1, 2],  // key = 7
      bsm[2, 3],  // key = 13
      bsm[2, 4],  // key = 14
      bsm[3, 1],  // key = 16
      bsm[4, 2]}; // key = 22

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
  auto [rowptr, col, vals] = bsm.export_BCSR();

  for (auto el : rowptr)
  {
    std::cout << el << " ";
  }

  std::cout << std::endl;

  for (auto el : col)
  {
    std::cout << el << " ";
  }

  std::cout << std::endl;

  for (auto el : vals)
  {
    std::cout << el << " ";
  }

  std::cout << std::endl;

  return 0;
}
