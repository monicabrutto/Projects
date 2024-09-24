/* Monica Brutto - Project 6 
*         MaxHeap.cpp - belongs to the MaxHeap.h. Creates constructors, destructor, getters and setters and other 
*                       functions used to modify the MaxHeap object. 
*/

#include "MaxHeap.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>

#define HEAP_MIN_SIZE 20

using namespace std; 

//----------------------------------------------------------------
// MaxHeap: creates a new array of HEAP_MIN_SIZE and sets size equal to HEAP_MIN_SIZE
//          sets count to 0
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
MaxHeap::MaxHeap(){
    heapArray = new int[HEAP_MIN_SIZE];
    size = HEAP_MIN_SIZE; 
    count = 0; 
}

//----------------------------------------------------------------
// MaxHeap: creates a new array of HEAP_MIN_SIZE and copies items from passed array. Heapifies
//          the heap.
//    Returns: 
//    Parameters: int* values - a pointer to the array of values that is heapified
//                int count - the number of items in the array values
//----------------------------------------------------------------
MaxHeap::MaxHeap(int * values, int count){
    heapArray = new int[HEAP_MIN_SIZE]; //create a new array
    size = HEAP_MIN_SIZE; 
    this->count = count; 
    while(this->count >= size){ //check the size of the array
        heapArray = sizeUp(); //set the heapArray to the new array
        size = size*2;
    }
    for(int i = 0; i < count; i++){ //copy the items into heapArray
        heapArray[i] = values[i];
    }

    int index = (count/2) - 1;  //find last item that is not a leaf node
    for(int i = index; i >= 0; i--){ //for all the parents in the heap, siftdown
        siftDown(i); 
    } 
}

//----------------------------------------------------------------
// MaxHeap: creates a new array of HEAP_MIN_SIZE and sets size and count to other
//          copies the content of other to heapArray
//    Returns: 
//    Parameters: const MaxHeap& other - the heap to be copied
//----------------------------------------------------------------
MaxHeap::MaxHeap(const MaxHeap& other){
    heapArray = new int[other.size]; //create a new array with the size of the copy
    size = other.size; 
    count = other.count;
    for(int i = 0; i < other.count; i++){ //copy all the items into this heapArray
        heapArray[i] = other.heapArray[i];
    }
}

//----------------------------------------------------------------
// ~MaxHeap: deletes the heapArray
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
MaxHeap::~MaxHeap(){
    delete[] heapArray;
}

//----------------------------------------------------------------
// offer: adds heapArray to the next available spot in the heap, sifts up the heap
//        and increases count by one.   
//    Returns: 
//    Parameters: int value - the value to be inserted into the heap
//----------------------------------------------------------------
void MaxHeap::offer(int value){
    while(count >= size){ //while size is less than count, sizeUp the heap
        heapArray = sizeUp();
        size = size*2; //adjust size
    }
    heapArray[count] = value;  //insert value into the last spot
    siftUp(); 
    count++;  //increase count
}

//----------------------------------------------------------------
// siftUp: loops through, starting at the end of the heap, if the current is larger than
//         it's parent swap the child and the parent 
//    Returns: 
//    Parameters:
//----------------------------------------------------------------
void MaxHeap::siftUp(){
    for(int i = count; i >= 0; i--){ //starting from the bottom of the heap, swap the childern with the parent
        if(heapArray[i] > heapArray[getParent(i)]){
            int swapValue = heapArray[i];
            heapArray[i] = heapArray[getParent(i)];
            heapArray[getParent(i)] = swapValue;
        }
    }
}

//----------------------------------------------------------------
// siftDown: loops through the heap, checks if the parent is greater than either of 
//           it's two childern, if yes, then swap with the biggest child
//    Returns: 
//    Parameters: 
//----------------------------------------------------------------
void MaxHeap::siftDown(int i){
    //if childern, are they bigger?
        //if yes, which is biggest?
            //swap
        //if no, return (base case)
    //call recursive frome new position
    if(i >= count/2){               //if there are no childern return
        return; 
    }
    
    int left = getLeftChild(i); //get left child
    int right = getRightChild(i); //get right child
    int highestChild = right; //set the highest to the right child

    if(right >= count){      //right does not exhist set the highest to left
        highestChild = left; 
    } else if(heapArray[left] > heapArray[right]) { //if the left val is bigger than the right, set highest to left
        highestChild = left; 
    }

    if(heapArray[highestChild] > heapArray[i]){ //if the highest value is greater than parent value, make the swap
        int swapValue = heapArray[i];
        heapArray[i] = heapArray[highestChild];
        heapArray[highestChild] = swapValue; 
        siftDown(highestChild);                 //call siftDown on the next child position which is highest
    }
    
}

//----------------------------------------------------------------
// sizeUp: creates a new array with double the size of the orginal, copies 
//         all the items into the new array, deletes the old and returns the new
//    Returns: int* - pointer to the new array
//    Parameters: 
//----------------------------------------------------------------
[[nodiscard]]
int* MaxHeap::sizeUp(){
    int newSize = size *2; 
    int* newHeap = new int[newSize];  //create a new array with the doubled size

    for(int i = 0; i < newSize; i++){  //copy all the items into the new heap
        newHeap[i] = heapArray[i]; 
    }

    delete[] heapArray;  //delete the old one
    return newHeap;   //return the heap
}

//----------------------------------------------------------------
// sizeDown: creates a new array with half the size of the orginal, copies 
//         all the items into the new array, deletes the old and returns the new
//    Returns: int* - pointer to the new array
//    Parameters: 
//----------------------------------------------------------------
[[nodiscard]]
int* MaxHeap::sizeDown(){
    int newSize = size /2;      //get the newSize

    int* newHeap = new int[newSize];    //create a new array with the smaller size

    for(int i = 0; i < count; i++){
        newHeap[i] = heapArray[i];      //copy all the items into the new array
    }

    delete[] heapArray; //delete the old and return the new
    return newHeap; 
}


//----------------------------------------------------------------
// poll: Removes and returns the first item in the heap, sifts down to fix the heap
//       and corrects count. if the heap is empty throws an exeception
//    Returns: int - the first item in the heap
//    Parameters:
//----------------------------------------------------------------
int MaxHeap::poll(){
    if(isEmpty()){          //check if the heap is empty, throw an exception if it is
        throw exception();
    }

    int removed = heapArray[0];         //get the first item in the heapArray 
    heapArray[0] = heapArray[count-1];  //swap the last item with the first item

    count--;        //subtract one from count, so we don't search for something not there
    siftDown(0);    //siftDown starting at the root
    //check if it is less than half
    if(count <= size/2){        
        if(size != HEAP_MIN_SIZE){      //don't go smaller than 20
            heapArray = sizeDown();
            size = size/2;              //adjust size
        }
    }
    return removed;     //return the largest item
}

//----------------------------------------------------------------
// empty: checks if count, the numeber of items in the heap, is zero. 
//        if it is return true, there are no items, else return false
//    Returns: bool - true indicates the heap is empty
//    Parameters:
//----------------------------------------------------------------
bool MaxHeap::isEmpty() const{
    if(count == 0){
        return true;
    } else {
        return false; 
    }
}

//----------------------------------------------------------------
// peek: if the heap is empty throws an execption, else returns position 0 in the heap
//    Returns: int - the first item in the heap (largest)
//    Parameters:
//----------------------------------------------------------------
int MaxHeap::peek() const{
    if(isEmpty()){
        throw exception();
    } 
    return heapArray[0];        //return the first item
}

//----------------------------------------------------------------
// getParent: returns the position of the parent by calculating the position of the 
//            child -1 divided by 2, rounded down
//    Returns: int - the position of the parent
//    Parameters: int - the position of the child 
//----------------------------------------------------------------
int MaxHeap::getParent(int position){
    return (position-1)/2; 
}

//----------------------------------------------------------------
// getLeftChild: returns the position of the child by calculating the position of the 
//            parent times 2 plus 1
//    Returns: int - the position of the child
//    Parameters: int - the position of the parent 
//----------------------------------------------------------------
int MaxHeap::getLeftChild(int position){
    return position*2 + 1; 
}

//----------------------------------------------------------------
// getRightChild: returns the position of the child by calculating the position of the 
//            parent times 2 plus 2
//    Returns: int - the position of the child
//    Parameters: int - the position of the parent 
//----------------------------------------------------------------
int MaxHeap::getRightChild(int position){
    return position*2 + 2;
}

//----------------------------------------------------------------
// sorted: returns a vector of the sorted items from smallest to largest
//    Returns: vector<int> - a vecotr of integeres
//    Parameters:
//----------------------------------------------------------------
vector<int> MaxHeap::sorted() const{
    vector<int> sorted(count);      //create a new vector
    MaxHeap sort(*this);            //create a copy of the heap
    for(int i = count; i > 0; i--){     //poll the largest items and place it at the end of the vector
        sorted[i-1] = sort.poll();
    }
    return sorted; //return the vector 
}

//----------------------------------------------------------------
// operator=: creates a new array of HEAP_MIN_SIZE and sets size and count to other
//          copies the content of other to heapArray
//    Returns: MaxHeap& - returns a referece to the copy
//    Parameters: const MaxHeap& other - the heap to be copied
//----------------------------------------------------------------
MaxHeap& MaxHeap::operator=(const MaxHeap& other){
    delete[] heapArray;         //delete the current data
    heapArray = new int[other.size];    //create a new heap with the copy's size
    size = other.size; 
    count = other.count;
    for(int i = 0; i < other.count; i++){ //copy all the items into the new heapArray
        heapArray[i] = other.heapArray[i];
    }

    return *this;   //return the heapArray
}

//----------------------------------------------------------------
// print: loops through the heap and prints out all the items in the heap
//        with a comma sperating them
//    Returns: 
//    Parameters: ostream& - reference to ostream used to print
//----------------------------------------------------------------
void MaxHeap::print(ostream& os) const{
    os << "(";
    for(int i = 0; i < count-1; i++)
    {
        os << heapArray[i] << ", ";
    }
    os << heapArray[count-1];
    os << ")" << endl;
}

//----------------------------------------------------------------
// operator<<: calls print on the MaxHeap, with ostream and returns 
//    Returns: ostream& - a reference to ostream
//    Parameters: ostream& - reference to ostream used to print
//                const MaxHeap& - the Heap to be printed
//----------------------------------------------------------------
ostream& operator<<(ostream& os, const MaxHeap& me){
    me.print(os);
    return os;
}