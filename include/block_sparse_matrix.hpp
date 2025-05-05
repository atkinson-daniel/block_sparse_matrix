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
  DenseMatrix &operator[](int row, int col)
  {
    // initialize the space in the RBT with empty data
    data.insert(DenseMatrix(4, 4), row, col);
    return data.find(row, col)->data;
  };

  friend std::ostream &operator<<(std::ostream &os, BlockSparseMatrix &matrix)
  {
    for (int col_i = 0; col_i < matrix.num_cols; col_i++)
    {
      RedBlackTree<DenseMatrix>::Node *found_node = matrix.data.find(0, col_i);
      if (found_node != nullptr)
      {
        for (int i = 0; i < found_node->data.num_cols; i++)
        {
          os << found_node->data[0, i] << ' ';
        }
      }
    }
    return os;
  };

protected:
  RedBlackTree<DenseMatrix> data;
};

#endif // BLOCK_SPARSE_MATRIX_HPP