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
private:
  struct Node
  {
    T data;
    Color color;
    Node *left;
    Node *right;
  };
};

#endif // RED_BLACK_TREE_CPP