// Definition File MemorySystem.cpp 
// Defines MemorySystem.h 

// Modules needed 
#include "MemorySystem.h"
#include "GameEntities.h"
#include "RNG.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Constructor
Cache::Cache(): xp(0), sugar_amount(0){} // Set's values to 0 until a save file is loaded

// Accessors
int Cache::getXp(){ return this->xp; }
int Cache::getSugarAmount(){ return this->sugar_amount; }

string Cache::getGummyName(){ return this->gummy_name; }

// Mutators
void Cache::setXp(int xp){ this->xp = xp; }
void Cache::setSugarAmount(int sugar_amount){ this->sugar_amount = sugar_amount; }
void Cache::setGummyName(string new_name){ this->gummy_name = new_name; }

/* SAVE FILE DATA STRUCTURE */
/* FIRST LINE -> LAST LINE */

// gummy_bear_name { string }
// bear_type       { char }

/* Int type separated by spaces */

// level           { int }
// health          { int }
// attack          { int }
// special_attack  { int }
// defense         { int }
// special_defense { int }
// speed           { int }
// xp              { int }
// sugar_amount    { int }


// Memember Functions
void Cache::SaveGameProgress(GummyBear* user)
{
    ofstream save_file(this->save_file_path, ios::out);

    if(!save_file.is_open())
    {
        cout << "Error: saving game file" << endl;
        return;
    }

    // Parse user stats to save file
    Stats& user_stats = user->getStats();

    save_file << user->getBearName() << endl;
    save_file << user_stats.getBearType() << endl;
    save_file << user_stats.getLevel() << " ";
    save_file << user_stats.getHealth() << " ";
    save_file << user_stats.getAttack() << " ";
    save_file << user_stats.getSpecialAttack() << " ";
    save_file << user_stats.getDefense() << " ";
    save_file << user_stats.getSpecialDefense() << " ";
    save_file << user_stats.getSpeed() << " ";
    save_file << this->xp << " ";
    save_file << this->sugar_amount;

    // Ensure file data integrity
    save_file.flush();
    save_file.close();
}

int Cache::checkLevelUp(int level)
{
    // While enough xp level up
    while(xp >= ((level + 1) * 100))
    {
        // Remove xp needed to level up
        xp -= ((level + 1) * 100);
        level += 1;
        // Reward sugar allocated towards game memory
        cout << "Level up! Now, " << level << endl;
    }
    // Return new level to update gummy
    return level;
}

GummyBear* Cache::LoadGame()
{
    string bear_name;
    char bear_type;

    int level, health, attack, special_attack, defense, special_defense, speed, xp, sugar_amount;

    ifstream save_file(this->save_file_path);
    if(!save_file.is_open())
    {
        throw runtime_error("Failed to open save file");
    }

    // Parse Data
    getline(save_file, bear_name);
    save_file >> bear_type;
    save_file >> level >> health >> attack >> special_attack >> defense >> special_defense >> speed >> xp >> sugar_amount;
    save_file.ignore(); save_file.close(); // Ignore new lines, & close the file
    
    // Close file 
    save_file.close();

    // Set Data
    this->setXp(xp); this->setSugarAmount(sugar_amount);
    return new GummyBear(bear_name, bear_type, level, health, attack, special_attack, defense, special_defense, speed);
}

GummyBear* Cache::NewGame()
{
    // Variables
    char name_option;
    char bear_type;
    int rng_index;

    // Stat variables
    int health, attack, special_attack, defense, special_defense, speed;

    // List of possible names
    vector<string> gummyBearNames = {
        "Fizzy Whizzpopper",
        "Galactic Glitter",
        "Neon Nibble",
        "Punky Pineapple",
        "Zany Berry Blast",
        "Hyper Honeydew",
        "Kooky Kiwi",
        "Loony Lemon Drop",
        "Bizarre Berry",
        "Savage Sour Apple",
        "Vivid Vanilla Vortex",
        "Wild Whirlwind Watermelon",
        "Chaotic Cherry Bomb",
        "Rocket Razzmatazz",
        "Manic Mango Madness",
        "Freaky Fruit Fusion",
        "Psycho Pomegranate",
        "Outlandish Orange Orbit",
        "Groovy Grape Gush",
        "Crazy Cosmic Cantaloupe"
    };

    // size of list
    int name_vector_size = gummyBearNames.size() - 1;

    // User Defines Gummy Bear's Name
    cout << "Give your gummy bear a new name!\nNames will be randomly iterated.\nFind one you like? Enter Y\nWant a need one? Press any key to reroll" << endl;   // Prompt
    
    // Get random choice 
    RNG rng;
    rng_index = rng.getRandRange(0, name_vector_size);

    // Print the generated choice 
    cout << gummyBearNames.at(rng_index) << "? ";

    // Get line & ignore buffer
    cin >> name_option; 
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cout << endl;

    // Generate new option
    while (cin.fail() || name_option != 'Y') 
    {
        rng_index = rng.getRandRange(0, name_vector_size);
        cout << gummyBearNames.at(rng_index) << "? ";
        cin >> name_option;
        
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << endl;
    }

    cout << "Chosen bear name: " << gummyBearNames.at(rng_index) << endl;

    // User Defines Gummy's Type
    cout << endl << "Choose your gummy's type:" << endl;
    cout << "Q = Quantum Type\nB = Brute Type\nM = MultiColor Type" << endl;
    cout << "Choose: ";
    cin >> bear_type;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    // Assures correct type
    while(bear_type != 'Q' && bear_type != 'B' && bear_type != 'M')
    {
        cout << endl;
        cout << "Error: Bear Type not 'Q', 'B', OR 'M' try again, ";
        cin >> bear_type;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    cout << endl;

    // Set Variables based on Gummy's Type
    switch (bear_type) {
    case 'Q': 
        // Quantum Type default stats
        health = 50;
        attack = 4;
        special_attack = 8;
        defense = 3;
        special_defense = 6;
        speed = 7;
        break;

    case 'B': 
        // Brute Type default stats
        health = 70;
        attack = 7;
        special_attack = 3;
        defense = 7;
        special_defense = 4;
        speed = 3;
        break;

    case 'M': 
        // MultiColor Type default stats
        health = 60;
        attack = 5;
        special_attack = 5;
        defense = 5;
        special_defense = 5;
        speed = 5;
        break;

    default:
        break;
    }

    // Placeholder for name bug fix 
    gummy_name = gummyBearNames.at(rng_index);

    // Return the new bear with default values
    return new GummyBear(gummyBearNames.at(rng_index), bear_type, 1, health, attack, special_attack, defense, special_defense, speed);
}

bool Cache::is_new_game()
{
    ifstream save_file(this->save_file_path);
    return save_file.peek() == ifstream::traits_type::eof(); // Checks whether file reaches end of file immediately 
}