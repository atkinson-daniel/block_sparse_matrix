# Block Sparse Matrix Container

## Introduction

This project implements an efficient block sparse matrix container. Block sparse matrices store non-zero matrices and their row and column position in the global block-matrix. This structure not only saves space but also allows for effective vectorization of operations intra-block, which enhances computational performance.

To manage the blocks, a Red-Black Tree is used, ensuring efficient O(log(n)) operations for block insertion, removal, and retrieval. Each node in the tree contains a dense matrix (represented as a vector), along with row and column indices, and maintains the standard red-black tree structure.

## How to run locally

1. Clone the Project using: `git@github.com:atkinson-daniel/block_sparse_matrix.git`
2. Configure and build the project with cmake.
3. Run the resulting executable named `main`.

You will a radomly generated block sparse matrix, it's stored red-black tree, the resulting block sparse matrix after eraser of a fixed block at row 1 col 0, the resulting red-black tree, and the BCSR output.

## Features

Block Sparse Matrix and Dense Matrix are publically accessible classes. The underlying storage via a Red Black Tree is meant to be obfuscated from the user. The user is allowed insert and remove from the Block Sparse Matrix.

### Block Sparse Matrix Insertion

The user is able to insert and retrieve a dense matrix into a block of the block sparse matrix by using the `[]` operator. The `[]` operator returns a reference to a pre-existing dense matrix if it's already been inserted, otherwise it inserts a zero block and gives back its reference. The user can insert a dense matrix by passing in a row value and a column value to the `[]` and obtain a reference that they can use as a lvalue to pass in an already created dense matrix by using `=` or modify the block in-place.

The project includes a function to print both the matrix and the red-black tree to the console. Given the seeded data in the main.cpp file, here's an example of what the matrix and red-black tree will look like when printed to the console:

<img width="217" alt="Screenshot 2025-05-05 at 9 04 14 PM" src="https://github.com/user-attachments/assets/2e12629f-aaf2-4543-8a6b-8b02278fd1e8" />

### Block Sparse Matrix Removal

The user is also able to remove a block from the block sparse matrix by using the `erase` method. The user passes in a row value and col valuse to the method. The method will then call upon the Red Black Tree class to locate the node, delete the node, and rebalance the tree when necessary.

After removal of a node, the print helper function shows the udpated matrix and red-black tree:

<img width="211" alt="Screenshot 2025-05-05 at 9 04 32 PM" src="https://github.com/user-attachments/assets/58bf95ea-1060-42b5-a00a-6affb7393b84" />

### DOK and BSCR Export

This project exports a block compressed sparse row (BSCR) format matrix for usage in optimized numerical methods (see [this resource](https://netlib.org/linalg/html_templates/node93.html) for more info). The user can access the `export_BSCR` method on the block sparse matrix to retrieve this information.

For the final obtain matrix after insertion and erasers, the screenshot below shows the cooresponding rowptr and col containers of the BCSR format:

<img width="214" alt="Screenshot 2025-05-05 at 9 11 40 PM" src="https://github.com/user-attachments/assets/019744d5-a6a3-4535-8954-26d7e3471234" />

## Storage Implementation with a Red Black Tree

Various data structures can be used to store a block sparse matrix, but this project leverages a red black tree for optimal efficiency. It offers significant flexibility, enabling the user to efficiently insert, remove, and retrieve blocks without needing to know the sparsity pattern of the matrix in advance. With prior knowledge of the sparsity patern, construction and retrevial of all blocks can be done with a hash map in O(n) complexity, with n being the number of blocks. Without prior knowledge (which is what this projects assumes from the user), this project's approach achieves O(N\*Log(n)). It's giving up a small logirthimic term, but allows full flexibility for the user. This is very useful when designing and testing numerical methods since at the beginning the final block structure might not be known. The exported BCSR format can be aligned in memory for efficient vectorization or parallel processing with efficient load-balancing.
