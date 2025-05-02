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
    Node *parent;
    // Calculate key based on position in matrix
    Node(T value, int row, int col, int num_cols) : data(value), key(num_cols * row + col), color(RED), left(nullptr), right(nullptr), parent(nullptr) {};
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
    bst_insert(node);
    node->color = RED;
    bst_rebalance(node);
    // TODO: Rebalance tree
  }

  Node &find(int row, int col)
  {
    int target_key = num_cols * row + col;
    Node *current_node = root;

    while (current_node != nullptr)
    {
      if (target_key < current_node->key)
      {
        current_node = current_node->left;
      }
      else if (target_key > current_node->key)
      {
        current_node = current_node->right;
      }
      else
      {
        return *current_node;
      }
    }

    throw std::runtime_error("Node not found");
  }

private:
  int num_cols;
  Node *root;

  void bst_insert(Node *new_node)
  {
    if (root == nullptr)
    {
      root = new_node;
      return;
    }

    Node *current_node = root;

    while (current_node != nullptr)
    {
      if (new_node->key < current_node->key)
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

  Node *RBTreeGetGrandparent(Node *node)
  {
    if (node->parent == nullptr)
    {
      return nullptr;
    }

    return node->parent->parent;
  }

  Node *RBTreeGetUncle(Node *node)
  {
    Node *grandparent = nullptr;
    if (node->parent != nullptr)
    {
      grandparent = node->parent->parent;
    }
    if (grandparent == nullptr)
    {
      return nullptr;
    }
    if (grandparent->left == node->parent)
    {
      return grandparent->right;
    }
    else
    {
      return grandparent->left;
    }
  }

  void bst_rebalance(Node *new_node)
  {
    if (new_node->parent == nullptr)
    {
      new_node->color = BLACK;
      return;
    }

    if (new_node->parent->color == BLACK)
    {
      return;
    }

    Node *parent = new_node->parent;
    Node *grandparent = RBTreeGetGrandparent(new_node);
    Node *uncle = RBTreeGetUncle(new_node);

    if (uncle != nullptr && uncle->color == RED)
    {
      uncle->color = BLACK;
      parent->color = BLACK;
      grandparent->color = RED;
      bst_rebalance(grandparent);
      return;
    }
    if (new_node == parent->right && parent == grandparent->left)
    {
      RBTreeRotateLeft(parent);
      new_node = parent;
      parent = new_node->parent;
    }
    else if (new_node == parent->left && parent == grandparent->right)
    {
      RBTreeRotateRight(parent);
      new_node = parent;
      parent = new_node->parent;
    }
    parent->color = BLACK;
    grandparent->color = RED;

    if (new_node == parent->left)
    {
      RBTreeRotateRight(grandparent);
    }
    else
    {
      RBTreeRotateLeft(grandparent);
    }
  }
};

#endif // RED_BLACK_TREE_CPP