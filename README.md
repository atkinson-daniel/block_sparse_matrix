# Block Sparse Matrix Container

## Introduction

This project implements an efficient block sparse matrix container. Block sparse matrices store non-zero elements in contiguous blocks. This structure not only saves space but also allows for effective vectorization inside each block, which enhances computational performance.

To manage the blocks, a Red-Black Tree is used, ensuring efficient O(log(n)) operations for block insertion, removal, and retrieval. Each node in the tree contains a dense matrix (represented as a vector), along with row and column indices, and maintains the standard red-black tree structure.

## Features

Block Sparse Matrix BlockSparseMatrixand Dense Matrix are publically accessible classes. The underlying storage via a Red Black Tree is meant to be obfuscated from the user. The user is allowed insert and remove from the Block Sparse Matrix.

### Block Sparse Matrix Insertion

The user is able to insert and retreive a dense matrix into a block of the block sparse matrix by using the `[]` operator. The `[]` operator returns a reference to a pre-existing dense matrix if it's already been inserted, otherwise it inserts a zero block and gives back its reference. The user can insert a dense matrix by passing in a row value and a column value to the `[]` and obtain a reference that they can use as a lvalue to pass in an already created dense matrix by using `=`.

### Block Sparse Matrix Removal

The user is also able to remove a block from the block sparse matrix by using the `erase` method. The user passes in a row value and col valuse to the method. The method will then call upon the Red Black Tree class to locate the node, delete the node, and rebalance the tree when necessary.

## Storage Implementation with a Red Black Tree

Various data structures can be used to store a block sparse matrix, but this project leverages a red black tree for optimal efficiency. It offers significant flexibility, enabling the user to efficiently insert, remove, and retrieve blocks without needing to know the sparsity pattern of the matrix in advance. With prior knowledge of the sparsity patern, construction and retrevial of all blocks is O(n) with n being the number of blocks. Without prior knowledge (which is what this projects assumes from the user), it's O(N\*Log(n)). It's giving up a small logirthimic term, but allows full flexibility for the user. This is very useful when designing and testing numerical methods since at the beginning the final block structure might not be known.

## Future Iterations

Ideally this project would export a block compressed sparse row (BSCR) format matrix for future usage in optimize numerical methods (see [this resource](https://netlib.org/linalg/html_templates/node93.html) for more info). A future feature would be to implement an `export_BSCR` method on the block sparse matrix to retrieve this information.
