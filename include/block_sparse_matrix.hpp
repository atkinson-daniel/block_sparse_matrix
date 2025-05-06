#ifndef BLOCK_SPARSE_MATRIX_HPP
#define BLOCK_SPARSE_MATRIX_HPP

#include <iostream>
#include <vector>
#include <dense_matrix.hpp>
#include <red_black_tree.hpp>

class BlockSparseMatrix
{
public:
  const int num_rows; // number of block rows
  const int num_cols; // number of block cols
  int b_rows;         // num of rows in a single block
  int b_cols;         // num of cols in a single block
  BlockSparseMatrix(int rows_, int cols_, int b_rows_, int b_cols_) : num_rows(rows_), num_cols(cols_), b_rows(b_rows_), b_cols(b_cols_), data(cols_) {};

  DenseMatrix &operator[](int row, int col)
  {
    // initialize the space in the RBT with empty data
    if (data.find(row, col) == nullptr)
    {
      data.insert(DenseMatrix(b_rows, b_cols), row, col);
    }

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

  void erase(int row, int col)
  {
    data.remove(row, col);
  };

  void print_tree()
  {
    data.print_tree();
  };

  std::tuple<std::vector<int>, std::vector<int>, std::vector<DenseMatrix>> export_DOK()
  {
    std::vector<int> row, col;
    std::vector<DenseMatrix> val;

    data.to_vector(data.get_root(), val, row, col);

    return std::make_tuple(row, col, val);
  }

  std::tuple<std::vector<int>, std::vector<int>, std::vector<DenseMatrix>> export_BCSR()
  {
    std::vector<int> rowptr;
    std::vector<int> col;
    std::vector<DenseMatrix> val;

    auto [row_dok, col_dok, val_dok] = export_DOK();

    rowptr.push_back(0);

    int row_n = 0;
    for (int i = 0; i < col_dok.size(); ++i)
    {
      val.push_back(val_dok[i]);
      col.push_back(col_dok[i]);

      if (row_n != row_dok[i])
      {
        // Return index
        rowptr.push_back(col.size() - 1);
        row_n = row_dok[i];
      }
    }

    rowptr.push_back(col.size());

    return std::make_tuple(rowptr, col, val);
  }

protected:
  RedBlackTree<DenseMatrix> data;
};

#endif // BLOCK_SPARSE_MATRIX_HPP