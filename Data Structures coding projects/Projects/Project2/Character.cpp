/*Monica Brutto
* Project 2 - Character Object belongs to Character.h, creates constuctor, getters and setters and 
*              other methods for the Character object. 
*/
#include "Character.h"
#include <iostream>
#include <iomanip> 
#include <random>
using namespace std; 


// Character: default constructor, sets the values string values to undefined and the int values to zero
Character::Character(){
    name = "undefined"; 
    role = "undefined";
    hitPoints = 0; 
    attackBonus = 0; 
    damageBonus = 0; 
    armorClass = 0; 
}

//----------------------------------------------------------------
// Character: constructs a Character Object by taking in parameters
//    Returns:
//    Parameters:
//       name (string) - name of the character 
//       role (string) - the type of character
//       hitPoints (int) - the character's current health. When it reaches zero, the character is dead
//       attackBonus (int)- value that is added to a character's attack roll to determine if an attack hits
//       damageBonus (int) - value that is added to a character's damage roll when attacking
//       armorClass (int) - value determines how hard a character is to hit
//----------------------------------------------------------------
Character::Character(string name, string role, int hitPoints, int attackBonus, int damageBonus, int armorClass){
    this->name = name; 
    this->role = role; 
    this->hitPoints = hitPoints; 
    this->attackBonus = attackBonus;
    this->damageBonus = damageBonus; 
    this->armorClass = armorClass; 
}

//Getters and Setters

//----------------------------------------------------------------
// getHealth: returns an int of the chatacter's current hitPoints
//            hitPoints are the current Health of a Character
//    Returns: current hitPoints (int)
//    Parameters:
//----------------------------------------------------------------
int Character::getHealth(){
    return hitPoints; 
}

//----------------------------------------------------------------
// getArmorClass: returns an int of the chatacter's armorClass
//    Returns: armorClass (int)
//    Parameters:
//----------------------------------------------------------------
int Character::getArmorClass(){
    return armorClass; 
}

//----------------------------------------------------------------
// getName: returns a string of the chatacter's name
//    Returns: name (string)
//    Parameters:
//----------------------------------------------------------------
string Character::getName(){
    return name;
}

//----------------------------------------------------------------
// getRole: returns a string of the chatacter's role
//    Returns: role (string)
//    Parameters:
//----------------------------------------------------------------
string Character::getRole(){
    return role;
}

//----------------------------------------------------------------
// attack: Rolls a 20 sided die, and adds that to the attacking 
//         character's attackBonus. The attack hits if the attackBonus
//         is great than or equal to the other character's armorClass.
//         If the attack hits, a 10 sided die is rolled and added to 
//         the attacking character's damage bonus. Then the damage is
//         subtracted from the other character's hit points. 
//    Returns: 
//    Parameters:
//         otherCharacter (Character) - reference to the non-attacking character
//----------------------------------------------------------------
void Character::attack(Character &otherCharacter){    
    
    int icosahedronDie = (rand() % 20) + 1 ;                // icosahdron is a 20 sided die, 1 - 20
    cout << "Attack Roll: " << icosahedronDie << " + " << attackBonus;
    attackBonus+= icosahedronDie;
    cout << " = " << attackBonus; 

//IF the attack hits, roll a 10-sided die and add the attacking character's damage bonus.
// Subtract the resulting amount from the opponent's hit points using the damage() method.
// else print out miss
    if(attackBonus >= otherCharacter.getArmorClass()){
        cout << " ---> HITS" << endl; 
        int DecagonDie = (rand() % 10) + 1; 
        cout << "Damage: " << DecagonDie << " + " << damageBonus; 
        damageBonus+= DecagonDie;
        cout << " = " << damageBonus << endl;
        otherCharacter.damage(damageBonus); 
    }
    else{
        cout << " ---> MISS" << endl; 
    }

}

//----------------------------------------------------------------
// damage: Takes in the amount of damage. If the amount is great than 
//         the character's hitpoints then hitPoints become zero, else
//         subtract the amount from the hitPoints. 
//    Returns: 
//    Parameters:
//         amount (int) - the amount of damage the character takes 
//----------------------------------------------------------------
void Character::damage(int amount){
    if(amount > hitPoints){
        hitPoints = 0; 
    } else {
        hitPoints-=amount;
    }
}

//----------------------------------------------------------------
// print: Takes in type of ostream as a reference and prints out
//        character details.
//    Returns: 
//    Parameters:
//         os (osstream) - reference to ostream object used to perfrom 
//                         output
//----------------------------------------------------------------
void Character::print(ostream& os){
    cout << "Character Summary" << endl; 
    cout << "-----------------------------" << endl; 
    os << name << " the " << role << endl; 
    os << "HP: " << hitPoints << endl; 
    os << "AB: " << attackBonus << endl; 
    os << "DB: " << damageBonus <<endl; 
    os << "AC: " << armorClass << endl; 
}


