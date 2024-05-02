// Definition File for RNG 

// Modules needed for program
#include "RNG.h"
#include "GameEntities.h"

#include <random>
#include <iostream>
#include <vector>

using namespace std;

/* RNG CLASS DESCRIBED */
// The purpose of this class is to automate & generate NPC's (Non-Playable Characters)
// Creating a system/algorithm that gives the NPC's some type of intelligence while in battle
// This gives the user a better experience because of the challenge 

// As the user progresses through the game the harder it gets 

// Define { RNG } @class Object

// Constructor
RNG::RNG(): wave_number(1){}

// Accessors
int RNG::getWaveNumber(){ return this->wave_number; }

// Mutators
void RNG::increaseWaveNumber(){ this->wave_number += 1; }

// Member functions

// Generates a wave of enemies based on RNG
vector<GummyBear*> RNG::spawnWave(int user_level)
{
    // Define amount of enemies to be spawned
    int number_to_spawn = wave_number + rand() % 4;

    // Define vector { wave } 
    vector<GummyBear*> wave;

    // Iterate to spawn gummies 
    for(int i = 0; i < number_to_spawn; i++)
    {
        // Set { boss_chance } to RNG & if lower than the session factor spawn a boss
        // Boss is more likely to spawn if it is the last index of the wave
        int boss_chance = rand() % 100;
        if(boss_chance < 15 + (wave_number * (i == number_to_spawn-1 ? 2.5 : 1.5)))
        {
            // Spawn a boss & set it to the current wave index
            wave.push_back(new GummyBear("Gorlock", getRandLevel(user_level)));
        }
        else
        {
            // Spawn a minion & set it to the current wave index
            wave.push_back(new GummyBear("Minion", getRandLevel(user_level)));
        }
    }

    // Returns a vector with GummyBear Type memory 
    return  wave;
}


// intelligence for enemy decision making
int RNG::evaluateMove(GummyBear* enemy, int user_level)
{
    // Prepare values that influence the move type an enemy should make
    // Output should be either: 1 = Attack || 2 = Block || 3 = Heal 

    // Enemy current params
    int current_enemy_health = enemy->getCurrentHealth();
    int current_enemy_speed  = enemy->getStats().getSpeed();

    // Thresholds that determines enemy decision
    int health_threshold = (30 + (3.5 * user_level));
    int speed_threshold  = (5 + (2 * user_level));

    // Enemy decision based on health status
    if(current_enemy_health < health_threshold)
    {
        // 50 % chance to heal else attack when health is low
        return getRandRange(1, 100) > 50 ? 3 : 1;
    }
    else
    {
        // Health is not low
        // Decisions based on speed
        if(current_enemy_speed > speed_threshold)
        {
            // Enemy is fast, thus more aggressive
            // 70% attack, 20% block, & 10% heal
            int probability = getRandRange(1, 100);

            if(probability <= 70) return 1;       // Attack
            else if(probability <= 90) return 2; // Block
            else return 3;                      // Heal
        }
        else
        {
            // Enemy is slower, thus more caution
            // 40% attack, 50% to block, & 10% heal
            int probability = getRandRange(1, 100);

            if(probability <= 40) return 1;       // Attack
            else if(probability <= 90) return 2; // Block
            else return 3;                      // Heal
        }
    }
}

// Player makes a move
int RNG::evaluateMove()
{
    // Define a defa
    int player_move_choice = 0;
    // Promp User to select a move 
    cout << "Your turn, make a move!" << endl;
    cout << "1. Attack\n2. Block\n3. Heal" << endl;
    cout << "Selection: ";

    // Get buffer
    cin >> player_move_choice;

    // Ensure proper move is made
    while((cin.fail()) || (player_move_choice != 1 && player_move_choice != 2 && player_move_choice != 3))
    {
        // Prompt user to try again
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";

        // Get buffer again and hope they don't continue the loop
        cin >> player_move_choice;
    }

    // Return player move used in the Colosseum
    return player_move_choice;
}

// Returns xp amount after defeating an enemy
int RNG::getXP(GummyBear* enemy)
{
    // Check for boss type
    bool is_boss = enemy->getBearName() == "Gorlock";

    // Boss entities give more xp
    double xpMultiplier = is_boss ? 2.5: 1.0;

    // Calc xp amount based on enemy level
    int xp = (xpMultiplier * (enemy->getStats().getLevel() + 10)); 
    return xp;
}


// Generates a random number within a specified range
int RNG::getRandRange(int first, int last)
{
    // Random seed engine
    random_device rand;
    mt19937       seed(rand());

    // Define the range, both endpoints are inclusive
    uniform_int_distribution<> distribution(first, last);

    // Return a randomly generated number from the given range
    return distribution(seed);
}


// Generates a random level number based on predetermined conditions
int RNG::getRandLevel(int user_level)
{
    // Define a random mutator
    // 0 = add | 1 = subtract | 2 = Stay
    int random_mutator_value = getRandRange(0, 2);

    // Declare int type variable for enemy level
    // Initially set to current user_level
    int level = user_level;

    switch (random_mutator_value) {
    case 0:
    {
        // Add to level based on RNG
        int add = getRandRange(0, 3);
        level += add;
        break;
    }

    case 1:
    {
        // Subtract level based on RNG
        int sub = getRandRange(0, 3);
        level -= sub;

        // Prevents a level lower than 1
        if(level < 1) level = 1;
        break;
    }
    
    default:
        // This code block is = 2
        // Which is already taken care of
        break;
    }

    // Return a randomly generated level
    return level;
}