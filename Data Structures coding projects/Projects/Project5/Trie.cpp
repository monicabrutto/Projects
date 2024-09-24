/*  Monica Brutto - Project 5 
*   Trie.cpp - Trie Object belongs to Trie.h Creates constuctors, destructor, getters and setters 
*           and other methods used to modify the Trie and Trie nodes.
*/

#include "Trie.h"
#include <string>
#include <vector>
using namespace std; 

//----------------------------------------------------------------
// Trie: Empty constuctor, creates a new root node, sets node count to 1 and word count to 0
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
Trie::Trie(){
    root = new Node(); 
    nodeCount = 1; 
    wordCount = 0; 
}

//----------------------------------------------------------------
// Trie: copy constuctor, gets the list of all words in other and inserts it into 
//      this Trie, copies root, wordCount and nodeCount. 
//    Returns: 
//    Parameters: const Trie& other
//----------------------------------------------------------------
Trie::Trie(const Trie& other){
    root = new Node();
    wordCount = other.wordCount;
    nodeCount = other.nodeCount; 
    vector<string> wordList = other.complete(""); //find all the words in other trie
    for(const string& word : wordList){ //for all the words in the vector, insert that word into this Trie
        insert(word); 
    }
}

//----------------------------------------------------------------
// ~Trie: destructor, calls clearTrie on root to recursivly loop through all childern 
//        and delete them
//    Returns: 
//    Parameters:
//----------------------------------------------------------------
Trie::~Trie(){
    clearTrie(root); 
}

 //----------------------------------------------------------------
    // clearTrie: recursivly loops through all childern and delete them
    //    Returns: 
    //    Parameters: const Trie& other
    //----------------------------------------------------------------
void Trie::clearTrie(Trie::Node*& current){
   for(int i = 0; i < current->children.size(); i++){
        if(current->children[i] != nullptr){
            clearTrie(current->children[i]);
        } 
   }

   delete current; 
    
}

//----------------------------------------------------------------
// insert: checks if the word is in the Trie, if true, set inserted to false
//         if the word is not the trie, insert the word, set inserted to true, increase word count.
//    Returns: bool - true indicates the word was inserted
//    Parameters: const string& word - the word to be inserted into the Trie
//----------------------------------------------------------------
bool Trie::insert(const string& word){
    //find if the word is in the Tire, no duplicates aloud. 
    bool isThere = find(word); 
    bool inserted; 
    if(isThere){
       inserted = false; 
    } else {
       inserted = insertHelper(root, word); // call insert Helper
        wordCount++; 
    }
   
    return inserted; 
} 

//----------------------------------------------------------------
// insertHelper: if the word lenghth is 0, meaning end of word then set isEndofWord to true
//               and return, else find the postion of the first letter in the array, if the pointer for that
//               letter is null, then create a new Node, else call inserteHelper on the next letter in the word
//    Returns: bool - true indicates the word was inserted
//    Parameters: Node* current - a pointer to the current node
//                const string& word - the word/letter to be inserted
//----------------------------------------------------------------
bool Trie::insertHelper(Trie::Node* current, const string& word){
   
    //base case
    if(word.length() == 0){
        current->isEndOfWord = true; 
        return true;
    }
    
    int index = word[0] - 'a'; //find the position in the array
    
    if(current->children[index] == nullptr){ //if the child is not there, then create a new node
        current->children[index] = new Node();
        nodeCount++; //increase new node count
    }

    return insertHelper(current->children[index], word.substr(1)); //add the next letter
}
//----------------------------------------------------------------
// count: returns the number of words in the Trie
//    Returns:
//    Parameters:
//----------------------------------------------------------------
int Trie::count() const {
    return wordCount; 
}
//----------------------------------------------------------------
// count: returns the number of nodes in the Trie
//    Returns:
//    Parameters:
//----------------------------------------------------------------
int Trie::getSize() const {
    return nodeCount; 
}
//----------------------------------------------------------------
// find: calls findHelper to recursive search for the word, returns true if the word is in the Trie
//    Returns: bool - true indicates that the word is in the tire
//    Parameters: const string& word - the word to be found
//----------------------------------------------------------------
bool Trie::find(const string& word) const {
    return findHelper(root, word); 
}

//----------------------------------------------------------------
// findHelper: recursive search for the word, returns true if the word is in the Trie
//             if word.length is 0 then return current->isEndOfWord, find the current postion 
//             in the array.(Hi Jon) if that pointer is null then the word is not in the trie, else search 
//             for the rest of the word. 
//    Returns: bool - true indicates that the word is in the tire
//    Parameters: Node* current - a pointer to the current node
//                const string& word - the word to be found
//----------------------------------------------------------------
bool Trie::findHelper(Trie::Node* current, const string& word) const {
    if(word.length() == 0){ //base case
        return current->isEndOfWord; //return true
    }

    int index = word[0] - 'a'; //find postiion in the alphabet
    if(current->children[index] == nullptr){ //if the letter's pointer is nullptr
        return false; //return false
    }

    return findHelper(current->children[index], word.substr(1)); //call inserthelper on current->childern[index] 
                                                                 // and the next letter 
}

//----------------------------------------------------------------
// completeCount: calls complete on the word and collects them in a vector, return the size of the vector
//    Returns: int - number of words that start with word
//    Parameters: const string& word - the word to be found
//----------------------------------------------------------------
int Trie::completeCount(const string& word) const{
    vector<string> wordList = complete(word); //find all the words that start with word
    return wordList.size(); //return size of the vector
}

//----------------------------------------------------------------
// complete: traverse to track the word given, i.e if the word is "ca" then follow the pointers, c then a
//           calls completeHelper on current, the word and the empty wordlist, to collect all the words. 
//    Returns: vector<string> - vecctor of strings that start with word 
//    Parameters: const string& word - the word to be found
//----------------------------------------------------------------
vector<string> Trie::complete(const string& word) const{
    vector<string> wordList; //empty vector 
    Node* current = root; //start at root
    for(int i = 0; i < word.length(); i++) //for all the letters in word
    {
        if(current == nullptr){
            return wordList; 
        }
        int nodeIndex = word[i] - 'a'; // find the position of the letter in the alphabet
        current = current->children[nodeIndex]; //set current to that pointer
    }
    completeHelper(current, word, wordList); //call completeHelper with current, word, and wordlist

    return wordList; 

}
//----------------------------------------------------------------
// completeHelper: if current is null return, if current is at the end of the word,
//                 add the word to the vector, for all the chars in the alpahbet, 
//                 recursivly search all chars a-z, concatenating the letter to the rest of the word
//    Returns:
//    Parameters: Node* current - a pointer to the current node
//                const string& word - the word to be found
//                vector<string> wordlist - the list of words that match
//----------------------------------------------------------------
void Trie::completeHelper(Trie::Node* current, const string& word, vector<string>& wordList) const{
    if(current == nullptr){ 
        return;    // base case
    }    
    
    if(current->isEndOfWord){ //if this the end of list add to vector
        wordList.push_back(word); 
    }

    //loop a-z to find all the possible words, concatenate the letter to the word to 
    for(char c = 'a'; c <= 'z'; c++){
        completeHelper(current->children[c - 'a'], word + c, wordList); 
    }

}

//----------------------------------------------------------------
// operator=: overloads, creates an exact copy of other to this node by getting a list
//            of all words and inserting it into this Trie
//    Returns: returns Trie& - a reference to a Trie
//    Parameters: const Trie& other - the Trie to be copied
//----------------------------------------------------------------
Trie& Trie::operator=(const Trie& other){ 
    root = new Node();
    wordCount = other.wordCount; //copy wordcount
    nodeCount = other.nodeCount; //copy nodecount
    vector<string> wordList = other.complete(""); 
    for(const string& word : wordList){ // for all the words in wordlist, insert word into in this Trie
        insert(word); 
    }

    return *this; 
}
//----------------------------------------------------------------
// prints: gets a vector of all words in the trie by calling complete() and prints them out
//    Returns: 
//    Parameters: ostream& os - the ostream to be used to print
//----------------------------------------------------------------
void Trie::print(ostream& os) const{
    vector<string> wordList = complete("");
    for(const string& word : wordList){
        os << word << endl; 
    }
}
//----------------------------------------------------------------
// operator<<: calls print on the Trie, with the ostream and returns
//    Returns: ostream& - returns an ostream reference
//    Parameters: ostream& os - the ostream to be used to print
//                const Trie& me - the Trie to be printed
//----------------------------------------------------------------
ostream& operator<<(ostream& os, const Trie& me){
    me.print(os); 
    return os; 
}



