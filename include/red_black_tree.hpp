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

  Node *root;
  RedBlackTree(int num_cols_) : root(nullptr), num_cols(num_cols_) {};

  // Test if data was set correctly
  Node *get_root()
  {
    return root;
  }
  // TODO: Modify later to avoid copy of data
  void insert(T data, int row, int col)
  {
    Node *node = new Node(data, row, col, num_cols);
    bst_insert(node);
    bst_rebalance(node);
    // TODO: Rebalance tree
  }

  void remove(int row, int col)
  {
    Node *node = find(row, col);

    if (node != nullptr)
    {
      bst_remove_node(node);
    }
  }

  Node *find(int row, int col)
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
        return current_node;
      }
    }

    return nullptr;
  }

private:
  int num_cols;

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
          new_node->parent = current_node;
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
          new_node->parent = current_node;
          current_node = nullptr;
        }
        else
        {
          current_node = current_node->right;
        }
      }
    }
  }

  Node *get_grandparent(Node *node)
  {
    if (node->parent == nullptr)
    {
      return nullptr;
    }

    return node->parent->parent;
  }

  Node *get_uncle(Node *node)
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

  bool set_child(Node *parent, std::string whichChild, Node *child)
  {
    if (whichChild != "left" && whichChild != "right")
    {
      return false;
    }

    if (whichChild == "left")
    {
      parent->left = child;
    }
    else
    {
      parent->right = child;
    }
    if (child != nullptr)
    {
      child->parent = parent;
    }
    return true;
  }

  bool replace_child(Node *parent, Node *currentChild, Node *newChild)
  {
    if (parent->left == currentChild)
    {
      return set_child(parent, "left", newChild);
    }
    else if (parent->right == currentChild)
    {
      return set_child(parent, "right", newChild);
    }
    return false;
  }

  void rotate_left(Node *node)
  {
    {
      Node *rightLeftChild = node->right->left;
      if (node->parent != nullptr)
      {
        replace_child(node->parent, node, node->right);
      }
      else
      {
        root = node->right;
        root->parent = nullptr;
      }

      set_child(node->right, "left", node);
      set_child(node, "right", rightLeftChild);
    }
  }

  void rotate_right(Node *node)
  {
    Node *leftRightChild = node->left->right;
    if (node->parent != nullptr)
    {
      replace_child(node->parent, node, node->left);
    }
    else
    { // node is root
      root = node->left;
      root->parent = nullptr;
    }
    set_child(node->left, "right", node);
    set_child(node, "left", leftRightChild);
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
    Node *grandparent = get_grandparent(new_node);
    Node *uncle = get_uncle(new_node);

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
      rotate_left(parent);
      new_node = parent;
      parent = new_node->parent;
    }
    else if (new_node == parent->left && parent == grandparent->right)
    {
      rotate_right(parent);
      new_node = parent;
      parent = new_node->parent;
    }
    parent->color = BLACK;
    grandparent->color = RED;

    if (new_node == parent->left)
    {
      rotate_right(grandparent);
    }
    else
    {
      rotate_left(grandparent);
    }
  }

  void bst_remove(int key)
  {
    Node *parent = nullptr;
    Node *cursor = get_root();

    while (cursor != nullptr)
    {
      if (cursor->key == key)
      {
        if (cursor->right == nullptr && cursor->left == nullptr)
        {
          if (parent == nullptr)
          {
            root = nullptr;
          }
          else if (parent->left == cursor)
          {
            parent->left = nullptr;
          }
          else
          {
            parent->right = nullptr;
          }

          delete cursor;
          return;
        }
        else if (cursor->right == nullptr)
        {
          if (parent == nullptr)
          {
            root = cursor->left;
          }
          else if (parent->left == cursor)
          {
            parent->left = cursor->left;
          }
          else
          {
            parent->right = cursor->right;
          }

          delete cursor;
          return;
        }
        else if (cursor->left == nullptr)
        {
          if (parent == nullptr)
          {
            root = cursor->right;
          }
          else if (parent->left == cursor)
          {
            parent->left = cursor->right;
          }
          else
          {
            parent->right = cursor->left;
          }

          delete cursor;
          return;
        }
        else
        {
          Node *successor_parent = cursor;
          Node *successor = cursor->right;

          while (successor->left != nullptr)
          {
            successor_parent = successor;
            successor = successor->left;
          }

          cursor->key = successor->key;

          if (successor_parent->left == successor)
          {
            successor_parent->left = successor->right;
          }
          else
          {
            successor_parent->right = successor->right;
          }

          delete successor;
          return;
        }
      }
      else if (cursor->key < key)
      {
        parent = cursor;
        cursor = cursor->right;
      }
      else
      {
        parent = cursor;
        cursor = cursor->left;
      }
    }
  }

  Node *get_sibling(Node *node)
  {
    if (node->parent != nullptr)
    {
      if (node == node->parent->left)
      {
        return node->parent->right;
      }

      return node->parent->left;
    }
    return nullptr;
  };

  Node *get_predecessor(Node *node)
  {
    node = node->left;
    while (node->right != nullptr)
    {
      node = node->right;
    }
    return node;
  };

  bool both_children_black(Node *node)
  {
    if (node->left != nullptr && node->left->color == RED)
    {
      return false;
    }
    if (node->right != nullptr && node->right->color == RED)
    {
      return false;
    }
    return true;
  };

  bool non_null_and_red(Node *node)
  {
    if (node == nullptr)
    {
      return false;
    }

    return (node->color == RED);
  }

  bool null_or_black(Node *node)
  {
    if (node == nullptr)
    {
      return true;
    }

    return (node->color == BLACK);
  }

  bool case1(Node *node)
  {
    if (node->color == RED || node->parent == nullptr)
    {
      return true;
    }

    return false;
  };

  bool case2(Node *node, Node *sibling)
  {
    if (sibling->color == RED)
    {
      node->parent->color = RED;
      sibling->color = BLACK;
      if (node == node->parent->left)
      {
        rotate_left(node->parent);
      }
      else
      {
        rotate_right(node->parent);
      }
      return true;
    }
    return false;
  };

  bool case3(Node *node, Node *sibling)
  {
    if (node->parent->color == BLACK &&
        both_children_black(sibling))
    {
      sibling->color = RED;
      prepare_for_removal(node->parent);
      return true;
    }

    return false;
  };

  bool case4(Node *node, Node *sibling)
  {
    if (node->parent->color == RED &&
        both_children_black(sibling))
    {
      node->parent->color = BLACK;
      sibling->color = RED;
      return true;
    }
    return false;
  };

  bool case5(Node *node, Node *sibling)
  {
    if (non_null_and_red(sibling->left) &&
        null_or_black(sibling->right) &&
        node == node->parent->left)
    {
      sibling->color = RED;
      sibling->left->color = BLACK;
      rotate_right(sibling);
      return true;
    }
    return false;
  }

  bool case6(Node *node, Node *sibling)
  {
    if (null_or_black(sibling->left) &&
        non_null_and_red(sibling->right) &&
        node == node->parent->right)
    {
      sibling->color = RED;
      sibling->right->color = BLACK;
      rotate_left(sibling);
      return true;
    }
    return false;
  }

  void prepare_for_removal(Node *node)
  {
    if (case1(node))
    {
      return;
    }

    Node *sibling = get_sibling(node);
    if (case2(node, sibling))
    {
      sibling = get_sibling(node);
    }
    if (case3(node, sibling))
      ;
    {
      return;
    }
    if (case4(node, sibling))
      ;
    {
      return;
    }
    if (case5(node, sibling))
    {
      sibling = get_sibling(node);
    }
    if (case6(node, sibling))
    {
      sibling = get_sibling(node);
    }

    sibling->color = node->parent->color;
    node->parent->color = BLACK;

    if (node == node->parent->left)
    {
      sibling->right->color = BLACK;
      rotate_left(node->parent);
    }
    else
    {
      sibling->left->color = BLACK;
      rotate_right(node->parent);
    }
  }

  void bst_remove_node(Node *node)
  {
    if (node->left != nullptr && node->right != nullptr)
    {
      Node *predecessor = get_predecessor(node);
      int predecessor_key = predecessor->key;
      bst_remove_node(predecessor);
      node->key = predecessor_key;
      return;
    }

    if (node->color == BLACK)
    {
      prepare_for_removal(node);
    }

    bst_remove(node->key);
  }
};

#endif // RED_BLACK_TREE_CPP