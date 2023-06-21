# Binary Search Tree

This C++ project provides an implementation of a Binary Search Tree (BST) data structure with a variety of operations such as insert, search, remove, select, split, and join. It also includes a unique function `insert_random` that inserts nodes randomly.

## Overview 

The code contains the following functions:

- **fix_size(Node *T)**: Updates the size of a node based on the number of its child nodes.
- **insert(Node *T, int k)**: Inserts a node with key `k` into the BST.
- **inorder_traversal(Node *T)**: Returns a vector of key values from an inorder traversal of the BST.
- **find(Node *T, int k)**: Searches for a node with key `k` in the BST and returns it if found.
- **select(Node *T, int r)**: Returns a node of rank `r` in the BST.
- **join(Node *L, Node *R)**: Joins two trees, where all keys in `L` are less than or equal to keys in `R`.
- **remove(Node *T, int k)**: Removes a node with key `k` from the BST.
- **split(Node *T, int k, Node **L, Node **R)**: Splits the tree `T` into two trees `L` and `R` based on key `k`.
- **insert_random(Node *T, int k)**: Inserts a node with key `k` into the BST at a random position.
- **printVector(vector<int> v)**: Prints the elements of a vector.

## How to Run

You can compile the program with a C++ compiler, e.g., `g++` or `clang++`. The `main` function is currently commented out, but it contains a series of tests that you can use to verify the functionality of the BST operations.

Uncomment the `main` function and then compile and run the program with:

```bash
$ g++ -o bst binarySearchTree.cpp
$ ./bst
