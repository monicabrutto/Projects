/* Monica Brutto - AVLTree.cpp
*  Project 4 - AVLTree Object belongs to AVLTree.H Creates constuctors, destructor, getters and setters 
*           and other methods used to modify the AVLTree and AVLTree nodes. 
*/
#include "AVLTree.h"
#include <string>
#include <vector>

//----------------------------------------------------------------
// AVLTree: Empty constuctor, sets root to null and numberofNodes to 0
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
AVLTree::AVLTree(){
    root = nullptr;
    numberOfNodes = 0; 
}


//----------------------------------------------------------------
// AVLTree: takes in the key and rootvalue to create a root node
//    Returns: 
//    Parameters: rootKey the key passed for the root node,
//             rootValue the value for the root node
//----------------------------------------------------------------
AVLTree::AVLTree(int rootKey, string rootValue){
    root = new Node(); 
    root->key = rootKey; 
    root->value = rootValue; 
    root->height = 0; 
    root->left = nullptr; 
    root->right = nullptr; 
    numberOfNodes = 1; 
}

//----------------------------------------------------------------
// AVLTree: Copy constuctor, copies the passed tree (other) to this tree
//          sets numberOfNodes and root and then calls copyHelper on root
//    Returns: 
//    Parameters:  other - const reference to the other tree, cannot change other
//----------------------------------------------------------------
AVLTree::AVLTree(const AVLTree& other){
    numberOfNodes = other.numberOfNodes;
    root = other.root; 
    copyHelper(root); 
}

//----------------------------------------------------------------
// copyHelper: recursively copies all nodes in the tree
//              copies key, value, height, and left and right pointers
//    Returns: Node * - a ponter to a node
//    Parameters: other - const node pointer to the other tree for copying
//----------------------------------------------------------------
AVLTree::Node* AVLTree::copyHelper(const Node* other){
    if(other == nullptr){
        return nullptr; 
    } else {
        Node* current = new Node; 
        current->key = other->key; 
        current->value = other->value; 
        current->height = other->height; 
        current->left = copyHelper(other->left);
        current->right = copyHelper(other->right);
        return current;  
    }

}
//----------------------------------------------------------------
// ~AVLTree: calls clearTreeHelper, to recursivly delete all the nodes in the Tree
//    Returns:
//    Parameters: 
//----------------------------------------------------------------
AVLTree::~AVLTree(){
    clearTreeHelper(root);
}

//----------------------------------------------------------------
// ~AVLTree: recursivly deletes all the nodes in the Tree
//           if the node is null return, else delete from the bottom up
//    Returns:
//    Parameters: Node*& current = pointer reference to current node
//----------------------------------------------------------------
void AVLTree::clearTreeHelper(AVLTree::Node*& current){
    //if the tree is null return
    if(current == nullptr){
        return; 
    } else {
        //delete the left most child
        clearTreeHelper(current->left);
        //delete the right most child
        clearTreeHelper(current->right);
        delete current;
    }
}
//----------------------------------------------------------------
// Insert: calls insert helper to insert a new node if the current at the end of the tree, returns
//               true if the node is inserted, false if the node is already in the tree
//    Returns: a boolean, true value indicates the node has been inserted
//    Returns: a boolean, true value indicates the node has been inserted
//    Parameters: int key - key of the new node 
//                string value - value of the new node 
//----------------------------------------------------------------
bool AVLTree::insert(int key, string value){
    return insertHelper(key, value, root);
}

//----------------------------------------------------------------
// InsertHelper: recurisivly adds a node to the tree, check the height and balance 
//         and then rotate if the balance is 2 or greater or -2 or less. Returns a bool if the node is inserted
//      Returns: a boolean - true indicates the node has been inserted
//      Parameters: int key - key of the new node 
//                string value - value of the new node 
//                Node*& current - reference to a pointer to the node we are traversing
//----------------------------------------------------------------
bool AVLTree::insertHelper(int key, string value, AVLTree::Node *& current){
    bool returnVal; 
    if (current == nullptr) {
        current = new AVLTree::Node(key, value);
        current->height = 0; 
        numberOfNodes++; 
        returnVal = true;
    } else if (key == current->key) { // base case
        returnVal = false;
    } else if (key < current->key) {
        returnVal = insertHelper(key, value, current->left); //add to the left
    } else {
        returnVal = insertHelper(key, value, current->right); //add to the right
    }
    
    current->height = fixHeight(current); 
    //check balance and rotate if ness
    int balance = getBalance(current);
    if(balance <= -2 || balance >= 2){
        int leftBalance = getBalance(current->left);
        int rightBalance = getBalance(current->right);
       //if balance is negative and matches hook
        if(balance < 0 && rightBalance < 0){
            singleLeftRotate(current, current->right);
        }
        //if balance is not negative and hook's balance mathces
        if(balance > 0 && leftBalance > 0){
            singleRightRotate(current, current->left);
        }
        //if balance is negative and hook's balance is opposite
        if(balance < 0 && rightBalance > 0){
            doubleLeftRotate(current);
        }
        //if balance is not negative and hook's balance is opposite
        if(balance > 0 && leftBalance < 0){
            doubleRightRotate(current);
        }
    }
    

    return returnVal; 
}

//----------------------------------------------------------------
// singleLeftRotate: performs a left rotation by setting a temp node to hook's left pointer
//                 setting hook's left to the problem, problem's right to the temp node 
//                 then problem to hook. Reassess the heights for the orginal hook and problem
//    Parameters: Node *& problem - the node that has the deppest off balance, reference to a pointer
//                Node * hook - the node to the right of the problem node, pointer
//----------------------------------------------------------------
void AVLTree::singleLeftRotate(AVLTree::Node *& problem, AVLTree::Node* hook) {
    Node* tempNode = hook->left;
    hook->left = problem; 
    problem->right = tempNode; 
    problem = hook; 
    hook->left->height = fixHeight(hook->left);
    problem->height = fixHeight(problem);

}

//----------------------------------------------------------------
// singleRightRotate: performs a right rotation by setting a temp node to hook's right pointer
//                 setting hook's right to the problem, problem's left to the temp node 
//                 then problem to hook. Reassess the heights for the orginal hook and problem
//    Parameters: Node *& problem - the node that has the deppest off balance, reference to a pointer
//                Node * hook - the node to the left of the problem node, pointer
//----------------------------------------------------------------
void AVLTree::singleRightRotate(AVLTree::Node *& problem, AVLTree::Node* hook) {
    Node* tempNode = hook->right;
    hook->right = problem; 
    problem->left = tempNode; 
    problem = hook; 
    hook->right->height = fixHeight(hook->right);
    problem->height = fixHeight(problem);
}

//----------------------------------------------------------------
// doubleLeftRotate: calls a single right roatate on the hook and hook's next node
//                  then a single left on the orginal problem and hook to perfrom a double left roatate
//    Parameters: Node *& current - the current node, and the orginal problem node
//----------------------------------------------------------------
void AVLTree::doubleLeftRotate(Node *& current){
 singleRightRotate(current->right, current->right->left);
 singleLeftRotate(current, current->right);
}

//----------------------------------------------------------------
// doubleRightRotate: calls a single left roatate on the hook and hook's next node
//                  then a single right on the orginal problem and hook to perfrom a double right roatate
//    Parameters: Node *& current - the current node, and the orginal problem node
//----------------------------------------------------------------
void AVLTree::doubleRightRotate(Node *& current){
 singleLeftRotate(current->left, current->left->right);
 singleRightRotate(current, current->left);
}

//----------------------------------------------------------------
// fixHeight: sets and recalculates the height of the current node
//    Returns: an int of the height of the node
//    Parameters: Node*& current - a pointer reference to the current node for the height to be changed
//----------------------------------------------------------------
int AVLTree::fixHeight(AVLTree::Node *& current){
  
    //if current does not exhists, return -1
    if(current == nullptr){
        return -1;
    }
    //base height
    int highestHeight = 0; 

    //if left child is not null, set the highest height to left's height plus 1
    if(current->left != nullptr){
        highestHeight = current->left->height + 1; 
    } 
    
    //if the right child is not null and the right's height is taller then the left,
    //set the hightest height to right's height plus 1 
    if(current->right != nullptr){  
        if(current->right->height >= highestHeight){
            highestHeight = current->right->height + 1; 
        }
    }

    return highestHeight; 
}

//----------------------------------------------------------------
// getBalance: returns the balance of the current node, passed to the function. 
//             height = leftHeight - rightHeight
//    Returns: an int of the balance of the current node
//    Parameters: Node*& current - a pointer reference to the current node
//----------------------------------------------------------------
int AVLTree::getBalance(AVLTree::Node*& current){
    // if the childern of the node is nullptr then return -1 else
    int leftHeight = -1; 
    int rightHeight = -1; 
    if(current == nullptr){
        return -1; 
    }
    // if the left child is not nullptr then set the leftHeight to the current left height
    if(current->left != nullptr){
        leftHeight = current->left->height; 
    }
    // if the right child is not nulltpr then set the rightHeight to the current right height
    if(current->right != nullptr){
        rightHeight = current->right->height;
    }
    //left->height - right->height
    return leftHeight - rightHeight; 
}

//----------------------------------------------------------------
// getHeight: returns the height of the whole AVLTree, which is the height of the node
//    Returns: an int of the height of the root node
//    Parameters: 
//----------------------------------------------------------------
int AVLTree::getHeight(){
    return root->height; 
}

//----------------------------------------------------------------
// getSize: returns the number of nodes in the tree
//    Returns: int, the number of nodes
//    Parameters: 
//----------------------------------------------------------------
int AVLTree::getSize(){
   return numberOfNodes;
}

//----------------------------------------------------------------
// operator=: copies the tree to this AVLTree, copies numberofNodes, root 
//            and then calls copyHelper to copy the rest of the tree    
//    Returns: A reference to a AVLTree
//    Parameters: const AVLTree& tree - reference to a AVLtree that is const, to be copied
//----------------------------------------------------------------
AVLTree& AVLTree::operator=(const AVLTree& tree){
    numberOfNodes = tree.numberOfNodes;
    root = tree.root; 
    copyHelper(root);

    return *this;
}
//----------------------------------------------------------------
// find: calls findHelper to recursivly search for a key and set the corresponding value in value
//    Returns: a boolean, true value indicates the key has been found
//    Parameters: int key - a target to search for 
//                string& value - sets this equal to the value found in the node
//                Node*& current - reference to a pointer to the node we are searching
//----------------------------------------------------------------
bool AVLTree::find(int key, string& value){
    return findHelper(key, value, root);
}

//----------------------------------------------------------------
// findHelper: returns true if the current key is equal to the target key 
//          Else if the target key is less than the current Key then search left.
//          If the target key is greater than search right. 
//    Returns: a boolean, true value indicates the key has been found
//    Parameters: int key - a target to search for 
//                string& value - sets this equal to the value found in the node
//                Node*& current - reference to a pointer to the node we are searching
//----------------------------------------------------------------
bool AVLTree::findHelper(int key, string& value, AVLTree::Node*& current){
    if(current == nullptr){
        return false;
    } else if(key == current->key){   // base case
        value = current->value; 
        return true; 
    } else if (key < current->key) {
        return findHelper(key, value, current->left); // search left 
    } else {
        return findHelper(key, value, current->right); //serach right
    }
}

//----------------------------------------------------------------
// findRange: creates a vector, calls findRangeHelper and returns the vector
//    Returns: a vector<string> that have the values in the range
//    Parameters: int lowkey - the lower bound of the range
//                int highkey - the upper bound of the range
//----------------------------------------------------------------
vector<string> AVLTree::findRange(int lowkey, int highkey){
    vector<string> inRange; 
    findRangeHelper(lowkey, highkey, root, inRange);
    return inRange; 
}

//----------------------------------------------------------------
// findRangeHelper: recursively traverses the tree in to find all the nodes with a key in 
//                  the range of lowkey and highkey and add them the vector passed. 
//    Returns: a vector<string> - a vector of values with keys found between lowkey and highkey
//    Parameters: int lowkey - the lower bound of the range
//                int highkey - the upper bound of the range
//                Node*& current - the current node in the tree
//                vector<string>& inRange - a vector of string values that is to be returned
//----------------------------------------------------------------
void AVLTree::findRangeHelper(int lowkey, int highkey, AVLTree::Node*& current, vector<string>& inRange){ 
    //if nullptr return
    if(current == nullptr){
        return;
    } 
    //if the current key could be anywhere in the left tree/subtree
    if(current->key >= lowkey){  
        findRangeHelper(lowkey, highkey, current->left, inRange);
    }
    //if the key is in the range, add it the vector
    if(current->key >= lowkey && current->key <= highkey){
        inRange.push_back(current->value);
    }
    //if the key could be anywhere in the right side of the tree/subtree
    if(current->key <= highkey){
        findRangeHelper(lowkey, highkey, current->right, inRange);
    }
}

//----------------------------------------------------------------
// printHelper: prints out a number of space from the depth of the node,
//              then prints out the key and value
//    Returns:
//    Parameters: int key - the int key value to be printed out 
//                string value - the string value, from the same node as key to be printed out
//                int depth  - the number of indents needed before printing
//                ostream& os - this lets us know what ostream to use
//----------------------------------------------------------------
void AVLTree::printHelper(int key, string value, int depth, ostream& os) const{
    for(int i = 0; i < depth; i++)
    {
        os << " "; 
    }
    os << key << ", " << value << endl; 
   
}

//----------------------------------------------------------------
// print: recursively traverses the tree in reverse order 
//                 starting with the right side, prints everything then root then the left. 
//    Returns:
//    Parameters: Node*& current - the current node in the tree
//                int depth  - the number of indents needed before printing
//                ostream& os - needed to pass to print to let it know what ostream to use
//----------------------------------------------------------------
void AVLTree::print(AVLTree::Node* const& current, int depth, ostream& os) const{
   if(current == nullptr){ //base case
        return; 
   }
   print(current->right, depth + 4, os);    //traverse the right side of the tree
   printHelper(current->key, current->value, depth, os); //print the current
   print(current->left, depth + 4, os); //traverse the left side of the tree
}

//----------------------------------------------------------------
// operator<<: calls print on root with a depth of 0, and passes os
//    Returns:
//    Parameters: ostream& os - needed to pass to print to let it know what ostream to use
//                const AVLTree& me - a reference to the AVLTree that is to be printed
//----------------------------------------------------------------
ostream& operator<<(ostream& os, const AVLTree& me){
    me.print(me.root, 0, os);
    return os;
}
