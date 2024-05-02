// Declaration File For MemorySystem.h


#ifndef MEMORYSYSTEM_H
#define MEMORYSYSTEM_H


// Include any modules needed for this File
#include "GameEntities.h"
#include <string>

using namespace std;

class Cache {
private:
    string const save_file_path = "Save\\save.txt"; // Save File Path

    int xp;            // Current Xp, used to update user level once a threshold is reached
    int sugar_amount; // Sugar is the in game currency used to train the Gummy
    
    // This is my last resort to fix the bug where it does not let me set a name for the gummy 
    string gummy_name;

public:
    // Constructor, set defualt 
    Cache();

    // Accessors
    int getXp();           // Return { xp } private member variable
    int getSugarAmount(); // Return { sugar_amount } private member variable
    
    string getGummyName(); // Returns { gummy_name } private member

    // Mutators
    void setXp(int);             // Updates { xp } private member variable
    void setSugarAmount(int);   // Updates { sugar_amount } private member variable
    void setGummyName(string); // Updates { gummy_name } private member variable


    // Member Functions
    void SaveGameProgress(GummyBear*); // Saves Current Game to File through passed variable { GummyBear& } parsing its attributes

    int checkLevelUp(int); // Checks if user leveled up and updates value according

    GummyBear* LoadGame(); // Loads the game's data, returning the use's gummy bear & progress
    GummyBear* NewGame(); // Loads menu for setting up a new game

    bool is_new_game(); // Checks whether game is new or if there is an existing game file
};

#endif