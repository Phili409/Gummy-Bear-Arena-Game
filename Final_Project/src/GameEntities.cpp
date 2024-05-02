// GameEntities.cpp 
// Definition File 
// Utilized to define class objects in @file { GameEntities.h }

// Import Declaration File & other needed Modules
#include "GameEntities.h"
#include <string>
#include <iostream>

using namespace std;


// Define @class { Stats }

// Constructors
Stats::Stats(char bear_type, int level, int health, int attack, int special_attack, int defense, int special_defense, int speed): bear_type(bear_type), level(level), health(health), attack(attack), special_attack(special_attack), defense(defense), special_defense(special_defense), speed(speed){}
Stats::Stats(){}

// Accessors
char Stats::getBearType(){ return this->bear_type; }

int Stats::getLevel(){ return this->level; }
int Stats::getHealth(){ return this->health; }
int Stats::getAttack(){ return this->attack; }
int Stats::getSpecialAttack(){ return this->special_attack; }
int Stats::getDefense(){ return this->defense; }
int Stats::getSpecialDefense(){ return this->special_defense; }
int Stats::getSpeed(){ return this->speed; }

// Mutators
void Stats::setBearType(char bear_type){ this->bear_type = bear_type;}
void Stats::setLevel(int level){ this->level = level;}
void Stats::setHealth(int health){ this->health = health;}
void Stats::setAttack(int attack){ this->attack = attack;}
void Stats::setSpecialAttack(int special_attack){ this->special_attack = special_attack;}
void Stats::setDefense(int defense){ this->defense = defense;}
void Stats::setSpecialDefense(int special_defense){ this->special_defense = special_defense;}
void Stats::setSpeed(int speed){ this->speed = speed;}


// Define @class { GummyBear }

// Constructors
GummyBear::GummyBear(string name, char bear_type, int level, int health, int attack, int special_attack, int defense, int special_defense, int speed): gummy_bear_name(name), current_health(health), is_player(true), stats(bear_type, level, health, attack, special_attack, defense, special_defense, speed){}

GummyBear::GummyBear(string gummy_bear_name, int level): gummy_bear_name(gummy_bear_name), is_player(false)
{
    // Init Minion
    if(gummy_bear_name == "Minion")
    {
        stats = Stats('E', level, (15 + (4 * level)), (3 + (2 * level)), (3 + (2 * level)), static_cast<int>(2 + (1.5 * level)), static_cast<int>(2 + (1.5 * level)), (2 * level));
        current_health = this->getStats().getHealth();
    }
    else if (gummy_bear_name == "Gorlock")
    {
        // Init Boss
        stats = Stats('E', level, (35 + (5 * level)), (5 + (3 * level)), (5 + (3 * level)), (4 + (3 * level)), (4 + (3 * level)), static_cast<int>(4 + (2.5 * level)));
        current_health = this->getStats().getHealth();
    }
}

// Destructor
GummyBear::~GummyBear(){ cout << "Bye Bye, " << gummy_bear_name << endl; }

// Accessors
string GummyBear::getBearName(){ return this->gummy_bear_name; }
Stats& GummyBear::getStats(){ return stats; }
int    GummyBear::getCurrentHealth() const { return current_health; }

// Mutators
void GummyBear::setBearName(string gummy_bear_name){ this->gummy_bear_name = gummy_bear_name;}
void GummyBear::setStats(Stats new_stats){ stats = new_stats; }
void GummyBear::setCurrentHealth(int new_health){ current_health = new_health; }

// Member Functions
void GummyBear::PrintStats()
{
    Stats current_stats = getStats();

    cout << "Name: "  << getBearName() << endl;
    cout << "Type: "  << current_stats.getBearType() << endl;
    cout << "Level: " << current_stats.getLevel() << endl;
    cout << endl;

    cout << "Health: " << current_health << "/" << current_stats.getHealth() << endl;
}

bool GummyBear::isPlayer() const { return is_player; }