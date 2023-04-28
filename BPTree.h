// Searching on a B+ tree in C++

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int MAX = 3;

// BP node
class Node
{
  bool IS_LEAF;
  int *key, size;
  Node **ptr;
  friend class BPTree;

public:
  Node();
};

// BP tree implementation inspired by https://www.programiz.com/dsa/b-plus-tree
class BPTree
{
  Node *root;
  void insertInternal(int, Node *, Node *);
  Node *findParent(Node *, Node *);

public:
  BPTree();
  void search(int);
  void insert(int);
  void display(Node *);
  Node *getRoot();
  void printLargestValues(Node *root, int &count, int n, set<int> &printedValues);
};

Node::Node()
{
  key = new int[MAX];
  ptr = new Node *[MAX + 1];
}

BPTree::BPTree()
{
  root = nullptr;
}

// Search operation
void BPTree::search(int x)
{
  if (root == nullptr)
  {
    cout << "Tree is empty\n";
  }
  else
  {
    Node *current = root;
    while (current->IS_LEAF == false)
    {
      for (int i = 0; i < current->size; i++)
      {
        if (x < current->key[i])
        {
          current = current->ptr[i];
          break;
        }
        if (i == current->size - 1)
        {
          current = current->ptr[i + 1];
          break;
        }
      }
    }
    for (int i = 0; i < current->size; i++)
    {
      if (current->key[i] == x)
      {
        cout << "Found\n";
        return;
      }
    }
    cout << "Not found\n";
  }
}

// Insert Operation
void BPTree::insert(int x)
{
  if (root == nullptr)
  {
    root = new Node;
    root->key[0] = x;
    root->IS_LEAF = true;
    root->size = 1;
  }
  else
  {
    Node *current = root;
    Node *parent;
    while (current->IS_LEAF == false)
    {
      parent = current;
      for (int i = 0; i < current->size; i++)
      {
        if (x < current->key[i])
        {
          current = current->ptr[i];
          break;
        }
        if (i == current->size - 1)
        {
          current = current->ptr[i + 1];
          break;
        }
      }
    }
    if (current->size < MAX)
    {
      int i = 0;
      while (x > current->key[i] && i < current->size)
        i++;
      for (int j = current->size; j > i; j--)
      {
        current->key[j] = current->key[j - 1];
      }
      current->key[i] = x;
      current->size++;
      current->ptr[current->size] = current->ptr[current->size - 1];
      current->ptr[current->size - 1] = nullptr;
    }
    else
    {
      Node *newLeaf = new Node;
      int virtualNode[MAX + 1];
      for (int i = 0; i < MAX; i++)
      {
        virtualNode[i] = current->key[i];
      }
      int i = 0, j;
      while (x > virtualNode[i] && i < MAX)
        i++;
      for (int j = MAX + 1; j > i; j--)
      {
        virtualNode[j] = virtualNode[j - 1];
      }
      virtualNode[i] = x;
      newLeaf->IS_LEAF = true;
      current->size = (MAX + 1) / 2;
      newLeaf->size = MAX + 1 - (MAX + 1) / 2;
      current->ptr[current->size] = newLeaf;
      newLeaf->ptr[newLeaf->size] = current->ptr[MAX];
      current->ptr[MAX] = nullptr;
      for (i = 0; i < current->size; i++)
      {
        current->key[i] = virtualNode[i];
      }
      for (i = 0, j = current->size; i < newLeaf->size; i++, j++)
      {
        newLeaf->key[i] = virtualNode[j];
      }
      if (current == root)
      {
        Node *newRoot = new Node;
        newRoot->key[0] = newLeaf->key[0];
        newRoot->ptr[0] = current;
        newRoot->ptr[1] = newLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;
      }
      else
      {
        insertInternal(newLeaf->key[0], parent, newLeaf);
      }
    }
  }
}

// Insert Operation
void BPTree::insertInternal(int x, Node *cursor, Node *child)
{
  if (cursor->size < MAX)
  {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--)
    {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--)
    {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  }
  else
  {
    Node *newInternal = new Node;
    int virtualKey[MAX + 1];
    Node *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++)
    {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX + 1; i++)
    {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX)
      i++;
    for (int j = MAX + 1; j > i; j--)
    {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--)
    {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
    {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
    {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root)
    {
      Node *newRoot = new Node;
      newRoot->key[0] = cursor->key[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    }
    else
    {
      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child)
{
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
  {
    return nullptr;
  }
  for (int i = 0; i < cursor->size + 1; i++)
  {
    if (cursor->ptr[i] == child)
    {
      parent = cursor;
      return parent;
    }
    else
    {
      parent = findParent(cursor->ptr[i], child);
      if (parent != nullptr)
        return parent;
    }
  }
  return parent;
}

// Print the tree
void BPTree::display(Node *cursor)
{
  if (cursor != nullptr)
  {
    for (int i = 0; i < cursor->size; i++)
    {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true)
    {
      for (int i = 0; i < cursor->size + 1; i++)
      {
        display(cursor->ptr[i]);
      }
    }
  }
}

// Get the root
Node *BPTree::getRoot()
{
  return root;
}
void BPTree::printLargestValues(Node *root, int &count, int n, set<int> &printedValues)
{
  if (root != nullptr)
  {
    if (root->IS_LEAF)
    {
      for (int i = root->size - 1; i >= 0 && count < n; i--)
      {
        if (printedValues.count(root->key[i]) == 0)
        {
          cout << root->key[i] << endl;
          printedValues.insert(root->key[i]);
          count++;
        }
      }
    }
    else
    {
      for (int i = root->size - 1; i >= 0 && count < n; i--)
      {
        printLargestValues(root->ptr[i + 1], count, n, printedValues);
        if (printedValues.count(root->key[i]) == 0)
        {
          cout << root->key[i] << endl;
          printedValues.insert(root->key[i]);
          count++;
        }
      }
      printLargestValues(root->ptr[0], count, n, printedValues);
    }
  }
}