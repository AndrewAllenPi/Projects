#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

/* Code to calculate the length of a Collatz sequence. A Collatz sequence is generated from any positive
** integer as the first element. All subsequent elements are calculated from the previous element as
** follows; if even divide by two and if odd multiply by three and add one. The sequence ends when the
** number one is reached.
** For example 15, 46, 23, 70, 35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1
** It is conjectured all such sequences end.
*/

// Next_term takes an input integer and outputs the next term of the Collatz sequence
int next_term(int a)
{
    if(a%2==0)
    {
        a=a/2;
    }
    else
    {
        a=3*a+1;
    }
    return a;
}

// Seq_length takes an input integer and calculates the length of the Collatz sequence
int seq_length(int a)
{
    if(a==1)
    {
        return 1;
    }
    int seqlength=2; // Counter for length of sequence. Increased from 1 as while loop stops when a=2
    while(next_term(a)!=1)
    {
        a=next_term(a);
        seqlength++;
    }
    return seqlength;
}
void printSequence(int n){
    while(n!=1){
        printf("%d ",n);
        n=next_term(n);
    }
    printf("%d \n",1);
}

struct node {
    int data;
    struct node* left;
    struct node* right;
};


struct node* newNode(int );
struct node* insert(struct node* , int );
struct node* collatz(int );
struct node* addLayerOfLeafs(struct node* );

/*
 Given a binary search tree, print out
 its data elements in increasing
 sorted order.
*/
void printTree(struct node* node) {
  if (node == NULL) return;

  printTree(node->left);
  printf("%d ", node->data);
  printTree(node->right);
}


int main()
{
    cout << "Next term for 3, 15, 13" << endl;
    cout << next_term(3) << endl
            << next_term(15) << endl
                << next_term(13) << endl;
    cout << "Sequence length for 3, 15, 13" << endl;
    cout << seq_length(3) << endl
            << seq_length(15) << endl
                << seq_length(13) << endl;
    cout << "Sequences for 3, 15, 13" << endl;
    printSequence(3);
    printSequence(15);
    printSequence(13);
    struct node* test = collatz(7);
    printTree(test);


}



/*
 Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).
*/
struct node* insert(struct node* node, int data) {
  // 1. If the tree is empty, return a new, single node
  if (node == NULL) {
    return(newNode(data));
  }
  else {
    // 2. Otherwise, recur down the tree
    if (data <= node->data) node->left = insert(node->left, data);
    else node->right = insert(node->right, data);

    return(node); // return the (unchanged) node pointer
  }
}
/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
*/
struct node* newNode(int data) {
  struct node* node = new(struct node);    // "new" is like "malloc"
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return(node);
}


/* Build Collatz tree of a size dependant on a

*/
struct node* collatz(int a){
    struct node* collatztree = newNode(1);
    for(int i=1; i<=a; i++)
    {
        collatztree = addLayerOfLeafs(collatztree);
    }
    return(collatztree);
}

/* Helper function to the collatz tree builder which recursively moves down the collatz tree and
   adds up to two child nodes when a node with no children is met.

*/
struct node* addLayerOfLeafs(struct node* node){
    if(node->left == NULL && node->right == NULL)
    {
        // test to see if a child node code be odd and rule out spurious cases
        if(((node->data-1)%3) == 0 && node->data != 1 && node->data != 4 )
        {
            insert(node,(node->data-1)/3);
        }
        insert(node,2*(node->data));
    }
    else if(node->left == NULL){
        addLayerOfLeafs(node->right);
    }
    else if(node->right == NULL){
        addLayerOfLeafs(node->left);
    }
    else{
        addLayerOfLeafs(node->right);
        addLayerOfLeafs(node->left);
    }
    return(node);
};


