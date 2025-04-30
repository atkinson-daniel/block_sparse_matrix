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
    Color color;
    Node *left;
    Node *right;
    Node(T value) : data(value), color(RED), left(nullptr), right(nullptr) {};
  };

  RedBlackTree() : root(nullptr) {};

  // Test if data was set correctly
  Node &get_root()
  {
    return *root;
  }
  // TODO: Modify later to avoid copy of data
  void insert(T data)
  {
    if (root == nullptr)
    {
      root = new Node(data);
      root->color = BLACK;
    }
  }

private:
  Node *root;
};

#endif // RED_BLACK_TREE_CPP