/*  Monica Brutto - Porject 5
*   Main.cpp - Builds a Tire based on the file wordlist_windows.txt, then prompts the user for a prefix to find
*              all the words in the file that begin with that prefix. Prints the completions based on user intput
*/

#include "Trie.h"
#include <iostream> 
#include <string> 
#include <fstream> //library to read in the file
using namespace std;

int main(){

    ifstream wordList("wordlist_windows.txt"); //create a stream called wordList
    string word;  //string that each word will be parsed to 
    Trie alphabetTrie;  // the Trie

    if(wordList.is_open()){ //if the file is able to be read
        while(wordList){    //while there is still something in the wordlist
            wordList >> word;   //take the next line from wordList and write it to word
            alphabetTrie.insert(word);  //insert into the trie
        }
    }
    
    //prompts the user to enter a prefix of lower case only and then gets the numebr of completions
    //then prompts the user again to print out the list of words that match that prefix
    //loops until the user hits enter at the prefix prompt
    while(true){
        string prefix; //string the user enters 
        string affirmation; //string to affirm if they want the completitions printed out
        cout << "Please enter a word prefix (or press enter to exit):  "; 
        getline(cin, prefix);
        cout << "\n" << endl; 

        //if the prefix is an enter then exit the loop
        if(prefix == ""){
           break;  
        }

        //find the count of the completions and print it out
        int count = alphabetTrie.completeCount(prefix); 
        cout << "There are " << count << " completions for the prefix " << "'" << prefix << "'. Show completitions? (y/n) "; 
        getline(cin, affirmation); 
        //check if affirmation is yes, if it is then get all the completions and print them out
        if(affirmation == "yes" || affirmation == "Yes" || affirmation == "y"){
            cout << "Completions" << endl; 
            cout << "----------------------------------" << endl; 
            vector<string> completitions; 
            completitions = alphabetTrie.complete(prefix);
            for(const string& word : completitions){    //for all the words in the vector completitions, print out the word
                cout << word << endl;
            }
        }
    }

}
