/* Monica Brutto - Project 6 Main.cpp
*         creates MaxHeap objects and runs all of the public functions in order to test, gives detailed output
*/

#include "MaxHeap.h"
#include <iostream>
#include <string>
#include <array>
#include <random>
using namespace std; 

int main(){
    srand(time(NULL)); //seed random
    cout << "Making a heap with random values, adding one at a time" << endl; 
    MaxHeap randomHeap; //create random heap
    for(int i = 0; i < 20; i++){ //add 20 random values from 1 to 100 in the heap
        int random = 1 + (rand() % 100); 
        randomHeap.offer(random);
        cout << "pass #" << i << " :" << randomHeap << endl;
    }
    cout << "randomHeap:" << randomHeap << endl;

    cout << "===========================================================================================================" << endl;

    cout << "Making a heap with from an array of values" << endl; 
    int arr[] = {12,21,54,64,80,66,48,39,5,14}; 
    MaxHeap heap(arr, 10); //use other constructor, to add the values of arr into the heap and test heapify
    cout << "heap:" << heap << endl;

    cout << "Making a copy with operator=" << endl; 
    MaxHeap copy; //make a empty heap
    copy = randomHeap;  //copy the heap using operator= method
    cout << "copy:" << copy;  
    cout << "randomHeap:" << randomHeap << endl; 
    cout << "changing copy by adding 88" << endl;
    copy.offer(88);    //change the copy, the orginal shouldn't change
    cout << "copy:" << copy;
    cout << "randomHeap:" << randomHeap << endl; 

    cout << "===========================================================================================================" << endl;


    cout << "Making a copy with constructor" << endl; //do the same thing as above but using the copy constructor
    MaxHeap copyConstructor(randomHeap); 
    cout << "copyConstructor:" << copyConstructor; 
    cout << "randomHeap:" << randomHeap << endl; 
    cout << "changing copy by adding 33" << endl;
    copyConstructor.offer(33);    
    cout << "copyConstructor:" << copyConstructor; 
    cout << "randomHeap:" << randomHeap << endl; 

    cout << "===========================================================================================================" << endl;


    cout << "poll copy" << endl; //poll and pint the biggest value
    cout << copy.poll() << endl; 
    cout << "copy:" << copy;

    cout << "peek at copy" << endl; //poll, just look at the biggest value, should still be in the heap
    cout << copy.peek() << endl; 
    cout << "copy:  " << copy;

    cout << "===========================================================================================================" << endl;

    cout << "\n" << endl;
    cout << "sorting copy" << endl; 
    vector<int> sortedCopy = copy.sorted(); //create a vector to collect the sorted values
    for(int i : sortedCopy){
        cout << i << " "; //print all the values in the vector
    }
    cout << endl;

    cout << "===========================================================================================================" << endl;

    cout << "the count is " << randomHeap.count << endl; 
    cout << "calling isEmpty on randomHeap: " << randomHeap.isEmpty() << endl; //check if the heap is empty, it shouldn't be

    cout << "===========================================================================================================" << endl;

    cout << "the size of randomHeap is " << randomHeap.size << endl; //check size
    cout << "add 20 more items to randomHeap" << endl;
    for(int i = 0; i < 20; i++){ //add 20 more random items to randomheap to test sizeUp
        int random = 1 + (rand() % 100); 
        randomHeap.offer(random); 
    }
    cout << randomHeap << endl; 
    cout << "the size is " << randomHeap.size << endl;  //check the size after, should be 40

    cout << "===========================================================================================================" << endl;

    cout << "\n" << endl;
    cout << "sorting randomHeap" << endl; //try sort again, using the same processes as above but with randomHeap
    vector<int> sortedRand = randomHeap.sorted(); 
    for(int i : sortedRand){
        cout << i << " "; 
    }
    cout << endl;

    cout << "===========================================================================================================" << endl;

    cout << "the size of randomHeap is " << randomHeap.size << endl; //check size
    cout << "remove all items from randomHeap" << endl; //poll all items from the heap to test sizeDown
    for(int i = 0; i < 40; i++){
        randomHeap.poll();
    }

    cout << "the size of randomHeap is " << randomHeap.size << endl; //check size
    cout << "the count is " << randomHeap.count << endl; 
    cout << "calling isEmpty: " << randomHeap.isEmpty() << endl;
}