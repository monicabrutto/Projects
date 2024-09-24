/* Monica Brutto - Project 6 
*         MaxHeap.h - defines the MaxHeap class for the object MaxHeap 
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>

#define HEAP_MIN_SIZE 20

using namespace std; 

class MaxHeap {

public: 

int* heapArray;  
int size; //size of the array
int count; //number of items

//----------------------------------------------------------------
// MaxHeap: creates a new array of HEAP_MIN_SIZE and sets size equal to HEAP_MIN_SIZE
//          sets count to 0
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
MaxHeap(); 

//----------------------------------------------------------------
// MaxHeap: creates a new array of HEAP_MIN_SIZE and copies items from passed array. Heapifies
//          the heap.
//    Returns: 
//    Parameters: int* values - a pointer to the array of values that is heapified
//                int count - the number of items in the array values
//----------------------------------------------------------------
MaxHeap(int * values, int count);

//----------------------------------------------------------------
// MaxHeap: creates a new array of HEAP_MIN_SIZE and sets size and count to other
//          copies the content of other to heapArray
//    Returns: 
//    Parameters: const MaxHeap& other - the heap to be copied
//----------------------------------------------------------------
MaxHeap(const MaxHeap& other); 

//----------------------------------------------------------------
// ~MaxHeap: deletes the heapArray
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
~MaxHeap();

//----------------------------------------------------------------
// offer: adds heapArray to the next available spot in the heap, sifts up the heap
//        and increases count by one.   
//    Returns: 
//    Parameters: int value - the value to be inserted into the heap
//----------------------------------------------------------------
void offer(int value); 

//----------------------------------------------------------------
// poll: Removes and returns the first item in the heap, sifts down to fix the heap
//       and corrects count. if the heap is empty throws an exeception
//    Returns: int - the first item in the heap
//    Parameters:
//----------------------------------------------------------------
int poll();

//----------------------------------------------------------------
// empty: checks if count, the numeber of items in the heap, is zero. 
//        if it is return true, there are no items, else return false
//    Returns: bool - true indicates the heap is empty
//    Parameters:
//----------------------------------------------------------------
bool isEmpty() const; 

//----------------------------------------------------------------
// peek: if the heap is empty throws an execption, else returns position 0 in the heap
//    Returns: int - the first item in the heap (largest)
//    Parameters:
//----------------------------------------------------------------
int peek() const;

//----------------------------------------------------------------
// sorted: returns a vector of the sorted items from smallest to largest
//    Returns: vector<int> - a vecotr of integeres
//    Parameters:
//----------------------------------------------------------------
vector<int> sorted() const; 

//----------------------------------------------------------------
// operator=: creates a new array of HEAP_MIN_SIZE and sets size and count to other
//          copies the content of other to heapArray
//    Returns: MaxHeap& - returns a referece to the copy
//    Parameters: const MaxHeap& other - the heap to be copied
//----------------------------------------------------------------
MaxHeap& operator=(const MaxHeap& other); 

//----------------------------------------------------------------
// print: loops through the heap and prints out all the items in the heap
//        with a comma sperating them
//    Returns: 
//    Parameters: ostream& - reference to ostream used to print
//----------------------------------------------------------------
void print(ostream& os) const;

//----------------------------------------------------------------
// operator<<: calls print on the MaxHeap, with ostream and returns 
//    Returns: ostream& - a reference to ostream
//    Parameters: ostream& - reference to ostream used to print
//                const MaxHeap& - the Heap to be printed
//----------------------------------------------------------------
friend ostream& operator<<(ostream& os, const MaxHeap& me);

private: 


void heapify();

//----------------------------------------------------------------
// sizeUp: creates a new array with double the size of the orginal, copies 
//         all the items into the new array, deletes the old and returns the new
//    Returns: int* - pointer to the new array
//    Parameters: 
//----------------------------------------------------------------
int* sizeUp();
//----------------------------------------------------------------
// sizeDown: creates a new array with half the size of the orginal, copies 
//         all the items into the new array, deletes the old and returns the new
//    Returns: int* - pointer to the new array
//    Parameters: 
//----------------------------------------------------------------
int* sizeDown();

//----------------------------------------------------------------
// siftUp: loops through, starting at the end of the heap, if the current is larger than
//         it's parent swap the child and the parent 
//    Returns: 
//    Parameters:
//----------------------------------------------------------------
void siftUp(); 

//----------------------------------------------------------------
// siftDown: loops through the heap, checks if the parent is greater than either of 
//           it's two childern, if yes, then swap with the biggest child
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
void siftDown(int i);

//----------------------------------------------------------------
// getParent: returns the position of the parent by calculating the position of the 
//            child -1 divided by 2, rounded down
//    Returns: int - the position of the parent
//    Parameters: int - the position of the child 
//----------------------------------------------------------------
int getParent(int);

//----------------------------------------------------------------
// getLeftChild: returns the position of the child by calculating the position of the 
//            parent times 2 plus 1
//    Returns: int - the position of the child
//    Parameters: int - the position of the parent 
//----------------------------------------------------------------
int getLeftChild(int);

//----------------------------------------------------------------
// getRightChild: returns the position of the child by calculating the position of the 
//            parent times 2 plus 2
//    Returns: int - the position of the child
//    Parameters: int - the position of the parent 
//----------------------------------------------------------------
int getRightChild(int);


};