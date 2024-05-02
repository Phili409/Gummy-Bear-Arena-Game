// GameEntities.h
// Declaration File
// Utilized to declare entity (i.e., gummies) classes
// Classes declared here are utilized as Playable OR Non-Playable Characters 

// Init Declaration
#ifndef GAMEENTITIES_H
#define GAMEENTITIES_H

// Imported Modules used for this file
#include <string>
using namespace std;

/* Declare Base @class { Stats } */
// This class will be the 'foundation' for both the enemy and player classes
class Stats
{
private: // Private Member Variables
    char   bear_type;           // Store gummy bear type as a Char abbreviation

    int level;                // Store the gummy bear's experience level 
    int health;              // Store the gummy bear's max health stat
    int attack;             // Store the gummy bear's physical attack stat 
    int special_attack;    // Store the gummy bear's special attack stat 
    int defense;          // Store the gummy bear's physical defense stat 
    int special_defense; // Store the gummy bear's special defense stat 
    int speed;          // Store the gummy bear's speed stat

public: // Public Members
    // Constructor
    Stats(char, int, int, int, int, int, int, int); // @class { Stats } Constructor
    Stats(); // Default
    
    // Accessors
    // Allows access to private variables
    char   getBearType();            // Returns { bear_type } private member

    int getLevel();                // Returns { level } private member
    int getHealth();              // Returns { health } private member
    int getAttack();             // Returns { attack } private member
    int getSpecialAttack();     // Returns { special_attack } private member
    int getDefense();          // Returns { defense } private member
    int getSpecialDefense();  // Returns { special_defense } private member
    int getSpeed();          // Returns { speed } private member

    // Mutators
    // Allows modification to private variables
    void setBearType(char);             // Updates the value of private member { bear_type }
    void setLevel(int);                // Updates the value of private member { level }
    void setHealth(int);              // Updates the value of private member { health }
    void setAttack(int);             // Updates the value of private member { attack }
    void setSpecialAttack(int);     // Updates the value of private member { special_attack }
    void setDefense(int);          // Updates the value of private member { defense }
    void setSpecialDefense(int);  // Updates the value of private member { special_defense }
    void setSpeed(int);          // Updates the value of private member { speed }
};

// Types of gummy bears
// 1. Quantum      - Faster, Stronger Specials | Low defense & health
// 2. Brute        - Slower, Stronger Physicals | Weaker to special damage 
// 3. MultiColor   - Balanced

// Each Gummy Bear Type affects it's default stats in @class { Stats }
// @class { GummyBear } 'Has-a' relation to @class { Stats }
// Depending on the chosen class the GummyBear's default stats will alter

/* Declare @class { GummyBear } */
class GummyBear {
private: // Private Class Members
    string gummy_bear_name;  // Store the given name of a gummy bear could be player made or computer determined
    Stats  stats;           // Store @var { stats } as a 'has-a' relation used to store the Gummy Bear's Stats
    int    current_health; // Store the current health amount for a Gummy Bear
    bool   is_player;     // Store validation for if a GummyBear object is a player or not
    
public: // Public Class Members
    // Constructor(s)
    // Defines @class { GummyBear } as well as constructing the private parameter { stats } based on Bear Class Params
    GummyBear(string, char, int, int, int, int, int, int, int);  // Player Constructor
    GummyBear(string, int); // Enemy Constructor

    // Destructor(s)
    ~GummyBear(); // Delete { stats } object to avoid memory leaks, outputs death message

    // Accessor(s)
    string getBearName();              // Returns { gummy_bear_name } private member
    Stats& getStats();                // Returns { stats } private member
    int    getCurrentHealth() const; // Returns { current_health } private member

    // Mutator(s)
    void setBearName(string);      // Updates the value of private member { gummy_bear_name }
    void setStats(Stats);         // Updates the value of private member { stats }
    void setCurrentHealth(int);  // Updated the value of private member { current_health }

    // Member Function(s)
    void PrintStats();       // Uses private member { stats } to print Gummy's stats to the terminal in a formatted way
    bool isPlayer() const;  // Returns { is_player } private member, validating the type of player
};
#endif