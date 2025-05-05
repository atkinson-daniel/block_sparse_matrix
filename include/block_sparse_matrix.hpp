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
  BlockSparseMatrix(int rows_, int cols_) : num_rows(rows_), num_cols(cols_), data(cols_) {};

private:
  RedBlackTree<DenseMatrix> data;
};

#endif // BLOCK_SPARSE_MATRIX_HPP