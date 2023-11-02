/*
The height of a node is the number of edges in
its longest chain of descendants.

Implement computeHeight to compute the height
of the subtree rooted at the node n. Note that
this function does not return a value. You should
store the calculated height in that node's own
height member variable. Your function should also
do the same for EVERY node in the subtree rooted
at the current node. (This naturally lends itself
to a recursive solution!)

Assume that the following includes have already been
provided. You should not need any other includes
than these.
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

//You have also the following class Node already defined.
//You cannot change this class definition, so it is
//shown here in a comment for your reference only:

class Node {
public:
  int height; // to be set by computeHeight()
  Node *left, *right;
  Node() { height = -1; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};
//*/

/*
//from BL, create a recursive function to count children
int countChildren(Node *n) {
  int h = 0, hLeft = 0, hRight = 0;
  
  //calculate # of children in each leg
  if (n->left) {
    hLeft++;
    //std::cout << "Found a child on left" << std::endl;
    hLeft += countChildren(n->left);
  }
  if (n->right) {
    hRight++;
    // std::cout << "Found a child on right" << std::endl;
    hRight += countChildren(n->right);
  }
  // wet height h equal to the longest leg
  // std::cout << "Left leg: " << hLeft << "vs Right leg: " << std::endl;
  hLeft >= hRight ? h = h+hLeft : h = h+hRight;
  std::cout << "**Setting height to" << h << std::endl;
  n->height = h;
  return h;
}
//also from BL
void computeHeight(Node *n) {
  // Implement computeHeight() here.
  Node *curr, *pre;
  curr = n;
  
  //BL: calculate the height of root
  curr->height = countChildren(n);

}
*/

void computeHeight(Node *n) {
  if (nullptr == n)
  {
    //std::out << "null, empty" << std::endl;
    return;
  }
  else
  {
    //std::cout << "calcing left sub tree" << std::endl;    
    Node *leftNode = n->left;
    computeHeight(leftNode);
    
    //std::cout << "calcing right sub tree" << std::endl;
    Node *rightNode = n->right;
    computeHeight(rightNode);
    
    if (nullptr == leftNode && nullptr == rightNode)
    {
      //current node is leaf node, height = 0
      n->height = 0;
    }
    else if (nullptr == leftNode && nullptr != rightNode)
    {
      //current node adds right node's height
      n->height = 1 + rightNode->height;
    }
    else if (nullptr == rightNode && nullptr != leftNode)
    {
      //current ode adds left node's height
      n->height = 1 + leftNode->height;
    }
    else
    {
      //current node has two sub-tree
      //ads the one with lihger height
      
      if(leftNode->height >= rightNode->height)
      {
        n->height = 1 + leftNode->height;
      }
      else
      {
        n->height = 1 + rightNode->height;
      }
    }
    
    return;
  }
  //end of if(nullptr == n)...else...
}

// This function prints the tree in a nested linear format.
void printTree(const Node *n) {
  if (!n) return;
  std::cout << n->height << "(";
  printTree(n->left);
  std::cout << ")(";
  printTree(n->right);
  std::cout << ")";
}

// The printTreeVertical function gives you a verbose,
// vertical printout of the tree, where the leftmost nodes
// are displayed highest. This function has already been
// defined in some hidden code.
// It has this function prototype: void printTreeVertical(const Node* n);

// This main() function is for your personal testing with
// the Run button. When you're ready, click Submit to have
// your work tested and graded.
int main() {
  Node *n = new Node();
  n->left = new Node();
  n->right = new Node();
  n->right->left = new Node();
  n->right->right = new Node();
  n->right->right->right = new Node();

  computeHeight(n);

  printTree(n);
  std::cout << std::endl << std::endl;
  //printTreeVertical(n); the course program has this function implemented
  
  // The Node destructor will recursively
  // delete its children nodes.
  delete n;
  n = nullptr;

  return 0;
}

/*
3(0()())(2(0()())(1()(0()())))


 [[Note] As a temporary fix for properly reporting the 
unit test's tree in the server output here, each newline 
will begin with a "#" symbol, which you can replace with 
a line break in your text editor for viewing. Padding spaces 
are shown as "." instead. Thanks for your patience! We'll 
improve this output soon.]  

##Height: 3
#|
#|_ Height: 0
#|..|
#|..|_ [null]
#|..|
#|..|_ [null]
#|
#|_ Height: 2
#...|
#...|_ Height: 0
#...|..|
#...|..|_ [null]
#...|..|
#...|..|_ [null]
#...|
#...|_ Height: 1
#......|
#......|_ [null]
#......|
#......|_ Height: 0
#.........|
#.........|_ [null]
#.........|
#.........|_ [null]
*/


