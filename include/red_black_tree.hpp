#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>
#include <vector>
#include <dense_matrix.hpp>

enum Color
{
  RED,
  BLACK
};

// Using template to make RBTree generic
template <typename T>
class RedBlackTree
{
public:
  struct Node
  {
    T data;
    int key;
    Color color;
    Node *left;
    Node *right;
    // Calculate key based on position in matrix
    Node(T value, int row, int col, int num_cols) : data(value), key(num_cols * row + col), color(RED), left(nullptr), right(nullptr) {};
  };

  RedBlackTree(int num_cols_) : root(nullptr), num_cols(num_cols_) {};

  // Test if data was set correctly
  Node &get_root()
  {
    return *root;
  }
  // TODO: Modify later to avoid copy of data
  void insert(T data, int row, int col)
  {
    Node *node = new Node(data, row, col, num_cols);
    // bst_insert(node);
    node->color = BLACK;
    root = node;
  }

private:
  int num_cols;
  Node *root;
  /*
  void bst_insert(Node *new_node)
  {
    if (*root == nullptr)
    {
      *root = new_node;
      return;
    }

    Node *current_node = *root;

    while (current_node != nullptr)
    {
      if (new_node->data < current_node->data)
      {
        if (current_node->left == nullptr)
        {
          current_node->left = new_node;
          current_node = nullptr;
        }
        else
        {
          current_node = current_node->left;
        }
      }
      else
      {
        if (current_node->right == nullptr)
        {
          current_node->right = new_node;
          current_node = nullptr;
        }
        else
        {
          current_node = current_node->right;
        }
      }
    }
  }
  */
};

#endif // RED_BLACK_TREE_CPP