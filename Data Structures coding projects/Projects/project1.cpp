#include <iostream>
#include <iomanip>
#include <random> //pulls in random library 
#include <cstdlib>
using namespace std; 


int main(){ 
    int const ARRAY_SIZE = 13; 
    int rolls = 0; 
    
    int * array = nullptr; //nullptr alias for null 
    array = new int[ARRAY_SIZE];

    // zero out array to ensure that all the content is empty, eventhough I used delete
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 0;
    }

    cout << "How many rolls? "; 
    cin >> rolls; 
    cout << "Simulating " << rolls << " rolls..." << endl; 

    srand(time(NULL));

    //rolls the dice, adds them up and then inserts into the correct array slot
    for(int i = 0; i < rolls; i++){
        int diceOne = (rand() % 6) + 1 ; // random numbers from one and six
        int diceTwo = (rand() % 6) + 1 ; // random numbers from one and six
        
        int sum = diceOne + diceTwo; 
        array[sum] = array[sum] + 1;
    }

    cout << "Results:" << endl; 

    //prints out the contents of the array in the given format
    for(int i = 2; i < ARRAY_SIZE; i++){
        cout << i; 
        cout << " was rolled "; 
        cout << array[i]; 
        cout << " times" << endl; 
    }

    delete [] array; 

}

