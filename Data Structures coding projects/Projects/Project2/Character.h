/*Monica Brutto
* Project 2 - Defines the Character Class for the Character Object
*/
#include <string>

using namespace std; 

// ---------------------------------------------------------
//  class Character: Defines a class of Character. Includes the following private variables: 
//                   name (string) - name of the character
//                   role (string) - type of the character (e.g. wizard, fighter, rogue, etc.).
//                   hitPoints (int) - the character's current health. 
//                   attackBonus(int) - value added to character's attack roll to determine if an attack hits
//                   damageBonus (int) - value added to a character's damage roll when attacking. 
//                   armorClass (int) - value that determines how hard a character is to hit. 
class Character{
    private: 
        string name;   
        string role;        
        int hitPoints;   
        int attackBonus;    
        int damageBonus;    
        int armorClass;     

    public: 
       //Default constructor
        Character(); 

        // Parameterized constructor: 
        //           Parameters: two strings and four int(s)
        Character(string, string, int, int, int, int);

        // Getters and setters
        //----------------------------------------------------------------
        // getHealth: returns an int of the chatacter's current hitPoints
        //            hitPoints are the current Health of a Character
        //    Returns: current hitPoints (int)
        //    Parameters:
        //---------------------------------------------------------------- 
        int getHealth(); 

        //----------------------------------------------------------------
        // getArmorClass: returns an int of the chatacter's armorClass
        //    Returns: armorClass (int)
        //    Parameters:
        //----------------------------------------------------------------
        int getArmorClass();

        //----------------------------------------------------------------
        // getName: returns a string of the chatacter's name
        //    Returns: name (string)
        //    Parameters:
        //----------------------------------------------------------------
        string getName();

        //----------------------------------------------------------------
        // getRole: returns a string of the chatacter's role
        //    Returns: role (string)
        //    Parameters:
        //---------------------------------------------------------------- 
        string getRole(); 

        //other methods

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
        void attack(Character &otherCharacter);

        //----------------------------------------------------------------
        // damage: Takes in the amount of damage. If the amount is great than 
        //         the character's hitpoints then hitPoints become zero, else
        //         subtract the amount from the hitPoints. 
        //    Returns: 
        //    Parameters:
        //         amount (int) - the amount of damage the character takes 
        //----------------------------------------------------------------
        void damage(int amount); 


        //----------------------------------------------------------------
        // print: Takes in type of ostream as a reference and prints out
        //        character details.
        //    Returns: 
        //    Parameters:
        //         os (osstream) - reference to ostream object used to perfrom 
        //                         output
        //----------------------------------------------------------------
        void print(ostream&); 


};

