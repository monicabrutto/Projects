/* Monica Brutto - AVLTree.h
* Project 4 - Defines the AVLTree class for an AVLTree Object
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std; 

class AVLTree {
private: 
//inner class for AVLTree
//Node Class - has left and right childern, key, value, and height
 class Node {
        public: 
            Node* left; //pointer to the left child
            Node* right; //pointer to the right child
            int key;  //key of the node
            string value; //value of the node
            int height;  //height of the node

            //emppty constructor, ensure left and right are nulltpr
            Node() : left(nullptr), right(nullptr){}
            
            // parameterized constructor, sets left and right to null and sets up key and value
            Node(int newKey, string newValue) : left(nullptr), right(nullptr), 
            key(newKey), value(newValue) {}

            // // parameterized constructor, sets left and right to null and sets up key, value, and height
            Node(int newKey, string newValue, int newHeight) : left(nullptr), right(nullptr), 
            key(newKey), value(newValue), height(newHeight) {}

            ~Node(){}
    }; 

//pointer to root node, first node in the tree has no parent
Node* root;

public: 
//the number of nodes in the whole tree
int numberOfNodes; 

//----------------------------------------------------------------
// AVLTree: Empty constuctor, sets root to null and numberofNodes to 0
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
AVLTree();

//----------------------------------------------------------------
// AVLTree: takes in the key and rootvalue to create a root node
//    Returns: 
//    Parameters: rootKey the key passed for the root node,
//             rootValue the value for the root node
//----------------------------------------------------------------
AVLTree(int rootKey, string rootValue); 

//----------------------------------------------------------------
// AVLTree: Copy constuctor, copies the passed tree (other) to this tree
//          sets numberOfNodes and root and then calls copyHelper on root
//    Returns: 
//    Parameters:  other - const reference to the other tree, cannot change other
//----------------------------------------------------------------
AVLTree(const AVLTree& tree); 

//----------------------------------------------------------------
// copyHelper: recursively copies all nodes in the tree
//              copies key, value, height, and left and right pointers
//    Returns: Node * - a ponter to a node
//    Parameters: other - const node pointer to the other tree for copying
//----------------------------------------------------------------
Node* copyHelper(const Node* other); 

//----------------------------------------------------------------
// ~AVLTree: calls clearTreeHelper, to recursivly delete all the nodes in the Tree
//    Returns:
//    Parameters: 
//----------------------------------------------------------------
~AVLTree(); 

//----------------------------------------------------------------
// ~AVLTree: recursivly deletes all the nodes in the Tree
//           if the node is null return, else delete from the bottom up
//    Returns:
//    Parameters: Node*& current = pointer reference to current node
//----------------------------------------------------------------
void clearTreeHelper(Node*& current);


//----------------------------------------------------------------
// Insert: calls insert helper to insert a new node if the current at the end of the tree, returns
//               true if the node is inserted, false if the node is already in the tree
//    Returns: a boolean, true value indicates the node has been inserted
//    Returns: a boolean, true value indicates the node has been inserted
//    Parameters: int key - key of the new node 
//                string value - value of the new node 
//----------------------------------------------------------------
bool insert(int key, string value); 

//----------------------------------------------------------------
// InsertHelper: recurisivly add a node to the tree, check the height and balance 
//         and then rotate if the balance is 2 or greater or -2 or less. Returns a bool if the node is inserted
//      Returns: a boolean - true indicates the node has been inserted
//      Parameters: int key - key of the new node 
//                string value - value of the new node 
//                Node*& current - reference to a pointer to the node we are traversing
//----------------------------------------------------------------
bool insertHelper(int key, string value, Node *& current);


//----------------------------------------------------------------
// singleLeftRotate: performs a left rotation by setting a temp node to hook's left pointer
//                 setting hook's left to the problem, problem's right to the temp node 
//                 then problem to hook. Reassess the heights for the orginal hook and problem
//    Parameters: Node *& problem - the node that has the deppest off balance, reference to a pointer
//                Node * hook - the node to the right of the problem node
//----------------------------------------------------------------
void singleLeftRotate(Node *& problem, Node* hook);

//----------------------------------------------------------------
// singleRightRotate: performs a right rotation by setting a temp node to hook's right pointer
//                 setting hook's right to the problem, problem's left to the temp node 
//                 then problem to hook. Reassess the heights for the orginal hook and problem
//    Parameters: Node *& problem - the node that has the deppest off balance, reference to a pointer
//                Node * hook - the node to the left of the problem node, pointer
//----------------------------------------------------------------
void singleRightRotate(Node *& problem, Node* hook);

//----------------------------------------------------------------
// doubleLeftRotate: calls a single right roatate on the hook and hook's next node
//                  then a single left on the orginal problem and hook to perfrom a double left roatate
//    Parameters: Node *& current - the current node, and the orginal problem node
//----------------------------------------------------------------
void doubleLeftRotate(Node *& current);

//----------------------------------------------------------------
// doubleRightRotate: calls a single left roatate on the hook and hook's next node
//                  then a single right on the orginal problem and hook to perfrom a double right roatate
//    Parameters: Node *& current - the current node, and the orginal problem node
//----------------------------------------------------------------
void doubleRightRotate(Node *& current);

//----------------------------------------------------------------
// fixHeight: sets and recalculates the height of the current node
//    Returns: an int of the height of the node
//    Parameters: Node*& current - a pointer reference to the current node for the height to be changed
//----------------------------------------------------------------
int fixHeight(Node *& current); 

//----------------------------------------------------------------
// getBalance: returns the balance of the current node, passed to the function. 
//    Returns: an int of the balance of the current node
//    Parameters: Node*& current - a pointer reference to the current node
//----------------------------------------------------------------
int getBalance(Node *& current); 

//----------------------------------------------------------------
// getHeight: returns the height of the whole AVLTree, which is the height of the node
//    Returns: an int of the height of the root node
//    Parameters: 
//----------------------------------------------------------------
int getHeight(); 

//----------------------------------------------------------------
// getSize: returns the number of nodes in the tree
//    Returns: int, the number of nodes
//    Parameters: 
//----------------------------------------------------------------
int getSize();

//----------------------------------------------------------------
// operator=: copies the tree to this AVLTree, copies numberofNodes, root 
//            and then calls copyHelper to copy the rest of the tree    
//    Returns: A reference to a AVLTree
//    Parameters: const AVLTree& tree - reference to a AVLtree that is const, to be copied
//----------------------------------------------------------------
AVLTree& operator=(const AVLTree& tree); 

//----------------------------------------------------------------
// find: calls findHelper to recursivly search for a key and set the corresponding value in value
//    Returns: a boolean, true value indicates the key has been found
//    Parameters: int key - a target to search for 
//                string& value - sets this equal to the value found in the node
//                Node*& current - reference to a pointer to the node we are searching
//----------------------------------------------------------------
bool find(int key, string& value);

//----------------------------------------------------------------
// findHelper: returns true if the current key is equal to the target key 
//          Else if the target key is less than the current Key then search left.
//          If the target key is greater than search right. 
//    Returns: a boolean, true value indicates the key has been found
//    Parameters: int key - a target to search for 
//                string& value - sets this equal to the value found in the node
//                Node*& current - reference to a pointer to the node we are searching
//----------------------------------------------------------------
bool findHelper(int key, string& value, Node *& current); 

//----------------------------------------------------------------
// findRange: creates a vector, calls findRangeHelper and returns the vector
//    Returns: a vector<string> that have the values in the range
//    Parameters: int lowkey - the lower bound of the range
//                int highkey - the upper bound of the range
//----------------------------------------------------------------
vector<string> findRange(int lowkey, int highkey);

//----------------------------------------------------------------
// findRangeHelper: recursively traverses the tree in to find all the nodes with a key in 
//                  the range of lowkey and highkey and add them the vector passed. 
//    Returns: a vector<string> - a vector of values with keys found between lowkey and highkey
//    Parameters: int lowkey - the lower bound of the range
//                int highkey - the upper bound of the range
//                Node*& current - the current node in the tree
//                vector<string>& inRange - a vector of string values that is to be returned
//----------------------------------------------------------------
void findRangeHelper(int lowkey, int highkey, Node*& current, vector<string>& inRange);

//----------------------------------------------------------------
// printHelper: prints out a number of space from the depth of the node,
//              then prints out the key and value
//    Returns:
//    Parameters: int key - the int key value to be printed out 
//                string value - the string value, from the same node as key to be printed out
//                int depth  - the number of indents needed before printing
//                ostream& os - this lets us know what ostream to use
//----------------------------------------------------------------
void printHelper(int key, string value, int depth, ostream& os) const; 

//----------------------------------------------------------------
// print: recursively traverses the tree in reverse order 
//                 starting with the right side, prints everything then root then the left. 
//    Returns:
//    Parameters: Node*& current - the current node in the tree
//                int depth  - the number of indents needed before printing
//                ostream& os - needed to pass to print to let it know what ostream to use
//----------------------------------------------------------------
void print(Node* const& current, int depth, ostream& os) const;
 
//----------------------------------------------------------------
// operator<<: calls print on root with a depth of 0, and passes os
//    Returns:
//    Parameters: ostream& os - needed to pass to print to let it know what ostream to use
//                const AVLTree& me - a reference to the AVLTree that is to be printed
//----------------------------------------------------------------
friend ostream& operator<<(ostream& os, const AVLTree& me); 



};