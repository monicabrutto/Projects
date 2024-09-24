/*  Monica Brutto - Project 5 
*   Trie.h - defines the Trie class for a object Trie
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std; 

class Trie {
private: 
    class Node {
        public: 
            array<Node*, 26> children; //array of 26 Node pointers called childern
            bool isEndOfWord; //bool for the end of word, if true it is the end of Word

            Node(): isEndOfWord(false), children{} {} //constructor, sets isEndOfWord to false, 
            //and all pointers in the array to null
            ~Node(){}
    };

public: 

    Node* root; //root node
    int wordCount; //the number of words in the Trie
    int nodeCount; //the number of nodes in the Trie

    //----------------------------------------------------------------
    // Trie: Empty constuctor, creates a new root node, sets node count to 1 and word count to 0
    //    Returns: 
    //    Parameters: 
    //----------------------------------------------------------------
    Trie(); 

    //----------------------------------------------------------------
    // Trie: copy constuctor, gets the list of all words in other and inserts it into 
    //      this Trie, copies root, wordCount and nodeCount. 
    //    Returns: 
    //    Parameters: const Trie& other
    //----------------------------------------------------------------
    Trie(const Trie& other); 

    //----------------------------------------------------------------
    // ~Trie: destructor, calls clearTrie on root to recursivly loop through all childern 
    //        and delete them
    //    Returns: 
    //    Parameters: const Trie& other
    //----------------------------------------------------------------
    ~Trie(); 

    //----------------------------------------------------------------
    // clearTrie: recursivly loops through all childern and deletes them
    //    Returns: 
    //    Parameters: const Trie& other
    //----------------------------------------------------------------
    void clearTrie(Node*& root);

    //----------------------------------------------------------------
    // insert: checks if the word is in the Trie, if true, set inserted to false
    //         if the word is not the trie, insert the word, set inserted to true, increase word count.
    //    Returns: bool - true indicates the word was inserted
    //    Parameters: const string& word - the word to be inserted into the Trie
    //----------------------------------------------------------------
    bool insert(const string&); 

    //----------------------------------------------------------------
    // insertHelper: if the word lenghth is 0, meaning end of word then set isEndofWord to true
    //               and return, else find the postion of the first letter in the array, if the pointer for that
    //               letter is null, then create a new Node, else call inserteHelper on the next letter in the word
    //    Returns: bool - true indicates the word was inserted
    //    Parameters: Node* current - a pointer to the current node
    //                const string& word - the word/letter to be inserted
    //----------------------------------------------------------------
    bool insertHelper(Node* current, const string& letter); 

    //----------------------------------------------------------------
    // count: returns the number of words in the Trie
    //    Returns:
    //    Parameters:
    //----------------------------------------------------------------
    int count() const;

    //----------------------------------------------------------------
    // count: returns the number of nodes in the Trie
    //    Returns:
    //    Parameters:
    //----------------------------------------------------------------
    int getSize() const;

    //----------------------------------------------------------------
    // find: calls findHelper to recursive search for the word, returns true if the word is in the Trie
    //    Returns: bool - true indicates that the word is in the tire
    //    Parameters: const string& word - the word to be found
    //----------------------------------------------------------------
    bool find(const string&) const;

    //----------------------------------------------------------------
    // findHelper: recursive search for the word, returns true if the word is in the Trie
    //             if word.length is 0 then return current->isEndOfWord, find the current postion 
    //             in the array, if that pointer is null then the word is not in the trie, else search 
    //             for the rest of the word. 
    //    Returns: bool - true indicates that the word is in the tire
    //    Parameters: Node* current - a pointer to the current node
    //                const string& word - the word to be found
    bool findHelper(Trie::Node* current, const string& word) const;

    //----------------------------------------------------------------
    // completeCount: calls complete on the word and collects them in a vector, return the size of the vector
    //    Returns: int - number of words that start with word
    //    Parameters: const string& word - the word to be found
    //----------------------------------------------------------------
    int completeCount(const string&) const; 

    //----------------------------------------------------------------
    // complete: traverse to track the word given, i.e if the word is "ca" then follow the pointers, c then a
    //           calls completeHelper on current, the word and the empty wordlist, to collect all the words. 
    //    Returns: vector<string> - vecctor of strings that start with word 
    //    Parameters: const string& word - the word to be found
    //----------------------------------------------------------------
    vector<string> complete(const string&) const; 

    //----------------------------------------------------------------
    // completeHelper: if current is null return, if current is at the end of the word,
    //                 add the word to the vector, for all the chars in the alpahbet, 
    //                 recursivly search all chars a-z, concatenating the letter to the rest of the word
    //    Returns:
    //    Parameters: Node* current - a pointer to the current node
    //                const string& word - the word to be found
    //                vector<string> wordlist - the list of words that match
    //----------------------------------------------------------------
    void completeHelper(Trie::Node* current, const string& word, vector<string>& wordList) const; 

    //----------------------------------------------------------------
    // operator=: overloads, creates an exact copy of other to this node by getting a list
    //            of all words and inserting it into this Trie
    //    Returns: returns Trie& - a reference to a Trie
    //    Parameters: const Trie& other - the Trie to be copied
    //----------------------------------------------------------------
    Trie& operator=(const Trie&); 

    //----------------------------------------------------------------
    // prints: gets a vector of all words in the trie by calling complete() and prints them out
    //    Returns: 
    //    Parameters: ostream& os - the ostream to be used to print
    //----------------------------------------------------------------
    void print(ostream& os) const;
    //----------------------------------------------------------------
    // operator<<: calls print on the Trie, with the ostream and returns
    //    Returns: ostream& - returns an ostream reference
    //    Parameters: ostream& os - the ostream to be used to print
    //                const Trie& me - the Trie to be printed
    //----------------------------------------------------------------
    friend ostream& operator<<(ostream& os, const Trie& me);

};