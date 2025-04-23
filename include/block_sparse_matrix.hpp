#ifndef BLOCK_SPARSE_MATRIX_HPP
#define BLOCK_SPARSE_MATRIX_HPP

#include <iostream>
#include <vector>
#include <dense_matrix.hpp>
#include <red_black_tree.hpp>

class BlockSparseMatrix
{
public:
  int num_rows;
  int num_cols;
  RedBlackTree<DenseMatrix> data;
};

#endif // BLOCK_SPARSE_MATRIX_CPP