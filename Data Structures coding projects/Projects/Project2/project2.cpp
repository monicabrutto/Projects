/*Monica Brutto
* Project 2 - Combat Simulator for a roll playing game that takes in two Character Objects and has them battle. 
*/
#include "Character.h"
#include <iostream>
#include <random>

using namespace std; 


//----------------------------------------------------------------
// main: Prompts the user for the first character deatils and construct 
//       the first character and Prints out their summary. Prompts the user 
//       for the second character details and prints out their summary. 
//       Then Simulates combat between the two characters until someone wins. 
//    Returns:
//    Parameters:
//----------------------------------------------------------------
int main(){
    //FirstChar means First Character, secondChar means Second Character
    string firstCharName, secondCharName, firstCharRole, secondCharRole; 
    
    int firstCharHitPoints, secondCharHitPoints, firstCharAttackBonus, 
    secondCharAttackBonus, firstCharDamageBonus, secondCharDamageBonus, 
    firstCharArmorClass, secondCharArmorClass;
    
    //Prompt user for the first Character's details
    cout << "First Character name?" << endl; 
    cin >> firstCharName;

    cout << firstCharName << "'s role?" << endl;
    cin >> firstCharRole; 

    cout << firstCharName << " the " << firstCharRole << "'s hit points?" << endl;
    cin >> firstCharHitPoints; 

    cout << firstCharName << " the " << firstCharRole << "'s attack bonus?" << endl;
    cin >> firstCharAttackBonus; 

    cout << firstCharName << " the " << firstCharRole << "'s damage bonus?" << endl;
    cin >> firstCharDamageBonus; 

    cout << firstCharName << " the " << firstCharRole << "'s Armor Class?" << endl;
    cin >> firstCharArmorClass; 

    //Create the character, called firstChar, and print out the summary
    Character firstChar(firstCharName, firstCharRole,firstCharHitPoints, firstCharAttackBonus, 
    firstCharDamageBonus, firstCharArmorClass);
    cout << endl;
    firstChar.print(cout);
    //--------------------------------------------------------------------------------------
    
    //Prompt the user for the details of the Second Character
    cout << "Second Character name?" << endl; 
    cin >> secondCharName;

    cout << secondCharName << "'s role?" << endl;
    cin >> secondCharRole; 

    cout << secondCharName << " the " << secondCharRole << "'s hit points?" << endl;
    cin >> secondCharHitPoints; 

    cout << secondCharName << " the " << secondCharRole << "'s attack bonus?" << endl;
    cin >> secondCharAttackBonus; 

    cout << secondCharName << " the " << secondCharRole << "'s damage bonus?" << endl;
    cin >> secondCharDamageBonus; 

    cout << secondCharName << " the " << secondCharRole << "'s Armor Class?" << endl;
    cin >> secondCharArmorClass; 

    //Create the second character, called secondChar, and print the summary
    Character secondChar(secondCharName, secondCharRole, secondCharHitPoints, secondCharAttackBonus, 
    secondCharDamageBonus, secondCharArmorClass);
    cout << endl;
    secondChar.print(cout);
    
    //Begin the simulated Combat
    cout << endl;
    cout << "Simulated Combat: " << endl; 

    //------------------------------------------------------------------------------
    // While 1 or true, the first character attacks by call attack 
    // and passing the second character as parameter, after the attack if
    // if the health of the second character is 0, meaning they are dead, then 
    // the first character wins and break the while loop. If not then the seocndChar attacks
    // and if the first Character has 0 heath then the second wins and break the loop. 
    //-------------------------------------------------------------------------------
    srand(time(NULL));  //seeds random to the time of the machine   
    while(1){
        cout << firstChar.getName() << " attacks!" << endl;
        firstChar.attack(secondChar); 
        cout << secondChar.getName() << " has " << secondChar.getHealth() << " hit points remaining" << endl; 
        if(secondChar.getHealth() == 0)
        {
            cout << firstChar.getName() << " wins!" << endl;
            break; 
        }
        
        cout << secondChar.getName() << " attacks!" << endl; 
        secondChar.attack(firstChar); 
        cout << firstChar.getName() << " has " << firstChar.getHealth() << " hit points remaining" << endl; 
        if(firstChar.getHealth() == 0){
            cout << secondChar.getName() << " wins!" << endl; 
            break;
        }
    }   
}