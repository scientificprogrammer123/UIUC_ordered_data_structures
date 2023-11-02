/*

Below, please implement the downHeap procedure for
a min heap data structure, which we will represent
as node-based tree for this exercise (not an array).

Remember A Min Heap Binary Tree is a Binary Tree where 
the root node has the minimum key in the tree.

The above definition holds true for all sub-trees in 
the tree. This is called the Min Heap property.

Almost every node other than the last two layers must 
have two children. That is, this is almost a complete 
binary tree, with the exception of the last 2 layers.

The below tree is an example of a min heap binary tree 
since the above two properties hold.

https://www.digitalocean.com/community/tutorials/min-heap-binary-tree

Suppose you are given a tree where the left and right
subtrees are min heaps, but the root node in particular
might not maintain the min heap property. Your code
should modify the tree rooted at Node* n so it is a
min heap. This means you need to satisfy the min heap
property: it is okay for a node's value to be equal to
one or both of its children, but the node's value must
not be greater than either of its children.

Tips:
Unlike the video lessons which demonstrated downHeap
implemented with an array implementation, this assignment
uses an ordinary binary tree with left and right child
pointers. This ordinary binary tree might not be complete
or balanced: any node might have only one child or the
other, or both, or neither. (You do not have to try to
balance the tree or turn it into a complete tree.)

If the root node exists, and if it has a left or right
child, and if one of the children has a smaller value
than the root node, then you should swap the root node
with the smaller child to move the large value down
into the tree. (This may need to be done recursively.)
Be careful to check whether pointers are null before
dereferencing them, as always; that includes using "->"
to access a class member through a pointer. In addition,
you must be careful not to accidentally compare "left"
and "right" pointers directly if you really intend to
compare the stored values "left->value" and "right->value".

Assume that these headers have already been included
for you:
*/

#include <iostream>
#include <string>

/*
You have the following class Node already defined.
You cannot change this class definition, so it is
shown here in a comment for your reference only:
*/

class Node {
public:
  int value;
  Node *left, *right;
  Node(int val = 0) { value = val; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};

/*
This function has also previously been defined for you:

void printTreeVertical(const Node* n);

You can use it to print a verbose, vertical diagram of
a tree rooted at n. In this vertical format, a left child
is shown above a right child in the same column. If no
child exists, [null] is displayed.

*/

void downHeap(Node *n) {

  // Implement downHeap() here.
  /*
    from https://devashish-iitg.medium.com/heap-sort-heapify-up-or-down-5fd35adfff39
    for heapify down, we start from the first node with a child, i.e.
    index = length(ar)/2-1, in this case it is 5/2-1 = 1, we floor any 
    decimal points I think.
    intial array: 1 3 2 5 4
    step 1: starting from index=1 (element=3), compare with child 5 and child 4
            and swap3 with 5
            1 5 2 3 4
    step 2: next we move to index = 0, (element=1), compare with child 5 and 2, 
            the swap 1with 5
            5 1 2 3 4
    step 3: next we compare 1 with 3 and 4 and swapping 1 and 4, we get
            5 4 2 3 1
    now 1 is the leaf node and cannot be moved.
    and now we have the max heap, where the largest number is on top.
  */

  //implementation borrowed from BL
  if (n->left) { //if left child exists, go down rabbit hole
    std::cout << "checking parent" << n->value << "vs left child";
    if (n->value < n->left->value) { //BL had <, but really we need to
                                     //swap if the node value is less than
                                     //child.
      //child is larger, so swap using a temp
      int temp = n->value;
      n->value = n->left->value;
      n->left->value = temp;
    }
    
    //use recursion on the left node
    std::cout << "moving down left to" << n->left->value << std::endl;
    downHeap(n->left);
  }  
  
  if (n->right) { //if right child exists, go down rabbit hole
    std::cout << "checking parent" << n->value << "vs right child";
    if (n->value < n->right->value) {
      int temp = n->value;
      n->value = n->right->value;
      n->right->value = temp;
    }
    
    //use recursion on right node 
    std::cout << "moving down right to" << n->right->value << std::endl;
    downHeap(n->right);
  }
}

// You can also use this compact printing function for debugging.
void printTree(Node *n) {
  if (!n) return;
  std::cout << n->value << "(";
  printTree(n->left);
  std::cout << ")(";
  printTree(n->right);
  std::cout << ")";
}

int main() {
  Node *n = new Node(100);
  n->left = new Node(1);
  n->right = new Node(2);
  n->right->left = new Node(3);
  n->right->right = new Node(4);
  n->right->right->right = new Node(5);

  downHeap(n);

  std::cout << "Compact printout:" << std::endl;
  printTree(n);
  std::cout << std::endl << "Vertical printout:" << std::endl;
  //printTreeVertical(n);

  delete n;
  n = nullptr;

  return 0;
}

