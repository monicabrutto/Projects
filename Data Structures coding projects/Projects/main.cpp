#include <iostream>
#include "Sequence.h"


int main(){

    Sequence x(10);
    x[0] =0; 
    x[1] =1;
    x[2] =2;
    x[3] =3;
    x[4] =4;
    x[5] =5;
    x[6] =6;
    x[7] =7;
    x[8] =8;
    x[9] =9;
 
    cout << x << endl;

    x.clear(); 

    cout << x << endl;

}