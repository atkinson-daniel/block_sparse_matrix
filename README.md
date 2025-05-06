# Block Sparse Matrix Container

## Introduction

This project implements an efficient block sparse matrix container. Block sparse matrices store non-zero dense submatrices along with their row and column positions in the global block matrix. This structure not only saves space but also allows for effective intra-block vectorization of operations, enhancing computational performance.

To manage the blocks, a Red-Black Tree is used, ensuring efficient `O(log(n))` operations for block insertion, removal, and retrieval. Each node in the tree contains a dense matrix (represented as a vector), along with its row and column indices, and maintains the standard Red-Black Tree properties.

## How to Run Locally

1. Clone the project using: `git@github.com:atkinson-daniel/block_sparse_matrix.git`
2. Configure and build the project with CMake.
3. Run the resulting executable named `main`.

You will see a randomly generated block sparse matrix, its Red-Black Tree representation, the resulting matrix after erasing a fixed block at row 1, column 0, the updated Red-Black Tree, and the exported BCSR output.

## Features

`BlockSparseMatrix` and `DenseMatrix` are publicly accessible classes. The underlying storage via the Red-Black Tree is meant to be abstracted away from the user. Users are allowed to insert into and remove blocks from the `BlockSparseMatrix`.

### Block Sparse Matrix Insertion

Users can insert and retrieve dense matrices using the `[]` operator. If a block already exists at the specified location, a reference to that block is returned. Otherwise, a zero-initialized block is inserted, and its reference is returned. Users can modify the block in-place or assign an existing dense matrix using the reference returned by the `[]` operator.

The project includes functions to print both the matrix and the Red-Black Tree to the console. Given the seeded data in `main.cpp`, here's an example of what the matrix and Red-Black Tree look like when printed:

<img width="217" alt="Screenshot 2025-05-05 at 9 04 14 PM" src="https://github.com/user-attachments/assets/2e12629f-aaf2-4543-8a6b-8b02278fd1e8" />

### Block Sparse Matrix Removal

Users can remove a block from the matrix using the `erase` method, which takes a row and column value. The method delegates to the Red-Black Tree to locate, delete, and rebalance the corresponding node.

After removing a node, the updated matrix and Red-Black Tree are printed using the helper function:

<img width="211" alt="Screenshot 2025-05-05 at 9 04 32 PM" src="https://github.com/user-attachments/assets/58bf95ea-1060-42b5-a00a-6affb7393b84" />

### DOK and BCSR Export

This project supports exporting to Block Compressed Sparse Row (BCSR) format, suitable for optimized numerical methods (see [this resource](https://netlib.org/linalg/html_templates/node93.html) for more info). Users can call the `export_BCSR` method on the `BlockSparseMatrix` to retrieve the compressed representation.

For the final matrix after insertions and erasures, the screenshot below shows the corresponding `rowptr` and `col` containers in the BCSR format:

<img width="214" alt="Screenshot 2025-05-05 at 9 11 40 PM" src="https://github.com/user-attachments/assets/019744d5-a6a3-4535-8954-26d7e3471234" />

## Storage Implementation with a Red-Black Tree

Various data structures can be used to store a block sparse matrix, but this project leverages a Red-Black Tree for optimal efficiency. It offers flexibility by allowing users to insert, remove, and retrieve blocks without requiring prior knowledge of the matrix's sparsity pattern.

If the sparsity pattern is known in advance, block construction and retrieval can be performed with a hash map in `O(n)` time, where `n` is the number of blocks. However, in this project (which assumes no prior knowledge), we achieve `O(N * log(n))` complexity. While this introduces a logarithmic overhead, it grants full flexibility - essential during the design and testing phases of numerical methods, when the final structure is not yet determined.

The exported BCSR format can be aligned in memory for efficient vectorization or parallel processing with proper load-balancing.

