#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
    T->size = 1;
    if (T->left) T->size += T->left->size;
    if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
    if (T == nullptr) return new Node(k);
    if (k < T->key) T->left = insert(T->left, k);
    else T->right = insert(T->right, k);
    fix_size(T);
    return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
    vector<int> inorder;
    vector<int> rhs;

    if (T == nullptr)
        return inorder;

    inorder = inorder_traversal(T->left);
    inorder.push_back(T->key);
    rhs = inorder_traversal(T->right);
    inorder.insert(inorder.end(), rhs.begin(), rhs.end());
    return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{
    // Check first node for key
    if (T == nullptr || T->key == k)
        return T;

    // Lower values to the left
    if (k < T->key)
        return find(T->left, k);

    // Higher values to the right
    return find(T->right, k);
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
    assert(T!=nullptr && r>=0 && r<T->size);
    int rank;

    // Check first Nodes rank
    if (T->left == nullptr)
        rank = 0;
    else
        rank = T->left->size;

    // Search tree by #rank
    if (rank > r)
        return select(T->left, r);

    else if (rank < r)
        return select(T->right, r-rank-1);

    return T;
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.
Node *join(Node *L, Node *R)
{
    // choose either the root of L or the root of R to be the root of the joined tree
    // (where we choose with probabilities proportional to the sizes of L and R)

    // Check for empty Nodes
    if (L == nullptr)
        return R;
    if (R == nullptr)
        return L;

    double chance = L->size / (L->size + R->size);
    double r = rand() % 101 / 100.0;

    if (r > chance)
    {
        R->left = join(L, R->left);
        fix_size(R);
        return R;
    }else
    {
        L->left = join(L, R->left);
        fix_size(R);
        return L;
    }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
    assert(T != nullptr);

    // Key value lies to the left
    if (k < T->key)
    {
        T->left = remove(T->left, k);
        fix_size(T);
        return T;

        // Key value lies to the right
    }else if (k > T->key)
    {
        T->right = remove(T->right, k);
        fix_size(T);
        return T;

    }else
    {
        // Root is Key value
        Node *temp = T;
        T = join(T->left, T->right);

        if(T != nullptr)
            fix_size(T);

        delete temp;
        return T;
    }
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
    // If tree is NULL
    if (T == nullptr)
    {
        *L = nullptr;
        *R = nullptr;
    }

    // If Key to Split lies to the left
    if (T->key <= k)
    {
        // But right side is NULL
        if (T->right == nullptr)
        {
            *L = T;
            *R = nullptr;

            // Split
        }else
        {
            split(T->right, k, L, R);
            T->right = *L;
            *L = T;
        }
        // Update size of tree
        if (*L != nullptr)
            fix_size(*L);

        // If Key to Split lies to the right
    }else
    {
        // But left side is NULL
        if (T->left == nullptr)
        {
            *R = T;
            *L = nullptr;

            // Split
        }else
        {
            split(T->left, k, L, R);
            T->left = *R;
            *R = T;
        }
        // Update size of tree
        if (*R != nullptr)
            fix_size(*R);
    }
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
    // If k is the Nth node inserted into T, then:
    // with probability 1/N, insert k at the root of T
    // otherwise, insert_random k recursively left or right of the root of T

    // If root is NULL
    if (T == nullptr)
    {
        Node *currentNode = new Node(k);
        return currentNode;
    }

    double r = rand() % 101 / 100.0;
    double rSize = rand() % T->size;

    if (rSize <= r)
    {
        Node *currentNode = new Node(k);
        split(T, k, &currentNode->left, &currentNode->right);
        fix_size(currentNode);

        return currentNode;

    }else if (k > T->key)
    {
        T->right = insert_random(T->right, k);
        fix_size(T);
        return T;

    }else
    {
        T->left = insert_random(T->left, k);
        fix_size(T);
        return T;
    }
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

//int main()
//{
//    Node *T = nullptr;
//    std::vector<int> test{5, 13, 2, 19, 3, 29, 11, 7, 17, 23};
//    for (int i=0; i<10; i++) T = insert_random(T, test[i]);
//    std::vector<int> inorder = inorder_traversal(T);
//
//    Node *val = select(T, 9);
//    //ASSERT_NE(val, nullptr);
//    if (val == nullptr)
//    {
//        std::cout << "val = select(T, 9): val expected to be a valid pointer, val is null (val == nullptr).\n";
//        return 1;
//    }
//    //ASSERT_EQ(val->key, 29);
//    if (val->key != 29)
//    {
//        std::cout << "expected/correct value for val->key is 29, actual value when testing " << val->key << ".\n";
//        return 1;
//    }
//    std::cout << "Passed" << std::endl;
//    return 0;
//}
