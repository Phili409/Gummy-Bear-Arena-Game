// Declaration File for RNG 
// Init File 
#ifndef RNG_H
#define RNG_H

// Modules needed
#include "GameEntities.h"

#include <random>
#include <iostream>
#include <vector>

using namespace std;

/* RNG CLASS DESCRIBED */
// The purpose of this class is to automate & generate NPC's (Non-Playable Characters)
// Creating a system/algorithm that gives the NPC's some type of intelligence while in battle
// This gives the user a better experience because of the challenge 

// Declare & Define { RNG } @class Object
class RNG {
private:
    int wave_number;

public:
    // Constructor
    RNG();

    // Accessors 
    int getWaveNumber();

    // Mutators
    void increaseWaveNumber();

    /* Member Functions */

    // Wave Spawner
    vector<GummyBear*> spawnWave(int);

    // Evaluate what is the best current move for a gummy
    // Attack, defend, or heal
    int evaluateMove(GummyBear*, int);

    // Non-overloaded method this one is for the player to make a move
    int evaluateMove();

    // Calculate the XP amount generated from defeating an enemy gummy
    // Bool type to see if the enemy is a boss or not
    int getXP(GummyBear*);

    // Get a random number from specified range
    int getRandRange(int, int);

    // Generate a level for the enemy
    int getRandLevel(int);
};
#endif