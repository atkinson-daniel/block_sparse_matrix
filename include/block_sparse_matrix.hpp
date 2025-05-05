#ifndef BLOCK_SPARSE_MATRIX_HPP
#define BLOCK_SPARSE_MATRIX_HPP

#include <iostream>
#include <vector>
#include <dense_matrix.hpp>
#include <red_black_tree.hpp>

class BlockSparseMatrix
{
public:
  int num_rows; // number of block rows
  int num_cols; // number of block cols
  int b_rows;   // num of rows in a single block
  int b_cols;   // num of cols in a single block
  BlockSparseMatrix(int rows_, int cols_, int b_rows_, int b_cols_) : num_rows(rows_), num_cols(cols_), b_rows(b_rows_), b_cols(b_cols_), data(cols_) {};
  DenseMatrix &operator[](int row, int col)
  {
    // initialize the space in the RBT with empty data
    data.insert(DenseMatrix(4, 4), row, col);
    return data.find(row, col)->data;
  };

  friend std::ostream &operator<<(std::ostream &os, BlockSparseMatrix &matrix)
  {
    for (int row = 0; row < matrix.num_rows; row++)
    {
      for (int b_row = 0; b_row < matrix.b_rows; b_row++)
      {
        for (int col = 0; col < matrix.num_cols; col++)
        {
          RedBlackTree<DenseMatrix>::Node *found_node = matrix.data.find(row, col);
          if (found_node != nullptr)
          {
            for (int b_col_idx = 0; b_col_idx < matrix.b_cols; b_col_idx++)
            {
              os << found_node->data[b_row, b_col_idx] << ' ';
            }
          }
          else
          {
            for (int b_col_idx = 0; b_col_idx < matrix.b_cols; b_col_idx++)
            {
              os << "0" << ' ';
            }
          }
        }
        os << std::endl;
      }
    }
    return os;
  };

protected:
  RedBlackTree<DenseMatrix> data;
};

#endif // BLOCK_SPARSE_MATRIX_HPP