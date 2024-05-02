// Actions.cpp 
// Definition File 
// Utilized to define class objects in @file { Actions.h }

// Import Declaration File & other needed Modules
#include "Actions.h"
#include "GameEntities.h"
#include <string>
#include <iostream>
#include <random>


/* DEFAULT MOVES */

// Define @class { DefaultAttack }'s member function
// This will be the default attack used by game entities
void DefaultAttack::attack(Actions& user, Actions& target, int attack_rate, char attack_type) const
{
    if(attack_type == 'P')
    {
        int target_defense = (target.getGummyBear()->getStats().getDefense() *  target.getDefenseMultiplier());

        int user_attack_damage = (user.getGummyBear()->getStats().getAttack() * user.getAttackMultiplier());

        int new_health = target.getGummyBear()->getCurrentHealth() - ((user_attack_damage / target_defense) * 5);

        target.getGummyBear()->setCurrentHealth(new_health);
    }
    else
    {
        int target_special_defense = (target.getGummyBear()->getStats().getSpecialDefense() *  target.getSpecialDefenseMulitplier());

        int user_special_damage = (user.getGummyBear()->getStats().getSpecialAttack() * user.getSpecialAttackMultiplier());

        int new_health = target.getGummyBear()->getCurrentHealth() - ((user_special_damage / target_special_defense) * 5);

        target.getGummyBear()->setCurrentHealth(new_health);
    }
}

// Define @class { DefaultBlock }'s member function
// This will be the default block used by game entities

// 75% chance of blocking an incoming attack, 25% chance of failure
bool DefaultBlock::block(Actions& user) 
{
    static random_device random;
    static mt19937 rng(random());
    static uniform_int_distribution<int> uniform(1, 4);

    int random_generated_number = uniform(rng); // Return a random number [1,4]

    return !(random_generated_number == 4);
}

// Define @class { DefaultHeal }'s member function
// This will be the default heal used by game entities
// Restore 20% of the user's health
void DefaultHeal::heal(Actions& user) 
{
    int healing_amount = (user.getGummyBear()->getStats().getHealth() * 0.20);
    user.getGummyBear()->setCurrentHealth(user.getGummyBear()->getCurrentHealth() + healing_amount);
}


/* SPECIAL MOVES */

// Define @class { ParticleBeam }'s member function
void ParticleBeam::attack(Actions& user, Actions& target, int attack_rate, char attack_type) const
{     
    if(attack_type == 'P')
    {
        int target_defense = (target.getGummyBear()->getStats().getDefense() *  target.getDefenseMultiplier());

        int user_attack_damage = (user.getGummyBear()->getStats().getAttack() * user.getAttackMultiplier());

        int new_health = target.getGummyBear()->getCurrentHealth() - ((user_attack_damage / target_defense) * 10);

        target.getGummyBear()->setCurrentHealth(new_health);
    }
    else
    {
        int target_special_defense = (target.getGummyBear()->getStats().getSpecialDefense() *  target.getSpecialDefenseMulitplier());

        int user_special_damage = (user.getGummyBear()->getStats().getSpecialAttack() * user.getSpecialAttackMultiplier());

        int new_health = target.getGummyBear()->getCurrentHealth() - ((user_special_damage / target_special_defense) * 10);

        target.getGummyBear()->setCurrentHealth(new_health);
    }
}

// Define @class { MudWall }'s member function
// User has 100% chance of blocking incoming enemy attack 
// User's gummy gets defense stat boost
bool MudWall::block(Actions& user)
{
    user.setDefenseMultiplier(user.getDefenseMultiplier() + 0.10); 
    user.setSpecialDefenseMultiplier(user.getSpecialDefenseMulitplier() + 0.10); 

    return true;
}

// Define @class { DivinePotion }'s member function
// User's Gummy restores full health
void DivinePotion::heal(Actions& user)
{ 
    user.getGummyBear()->setCurrentHealth(user.getGummyBear()->getStats().getHealth());     
}


/* Define @class Actions */

// Constructor
Actions::Actions(GummyBear* bear)
{
    // Init Action Object 
    switch (bear->getStats().getBearType())
    {
    case 'Q':
        // Quantum Type -> Stronger Special Damage, Weaker Physical Damage | Weaker Special Defense, Stronger Physical Defense
        attack_multiplier          = 0.80;
        special_attack_multiplier  = 1.20;
        defense_multiplier         = 1.50;
        special_defense_multiplier = 0.70;

        attack_type = 'S'; // Special Attacker
        break;

    case 'B':
        // Brute Type -> Stronger Physical Defense, Weaker Special Defense | Weaker Special Attack, Stronger Physical Attack
        attack_multiplier          = 1.20;
        special_attack_multiplier  = 0.80;
        defense_multiplier         = 1.50;
        special_defense_multiplier = 0.65;

        attack_type = 'P'; // Physical Attacker
        break;

    case 'M':
        // MultiColor Type -> Balanced Across
        attack_multiplier          = 1.00;
        special_attack_multiplier  = 1.00;
        defense_multiplier         = 1.00;
        special_defense_multiplier = 1.00;

        attack_type = 'P'; // Physical Attacker
        break;
    
    default:
        // Default type -> Balanced Across, but weaker
        attack_multiplier          = 0.70;
        special_attack_multiplier  = 0.70;
        defense_multiplier         = 0.70;
        special_defense_multiplier = 0.70;

        attack_type = 'P'; // TODO: RNG
        break;
    }

    // Every Gummy Type Starts with Default Moves
    attack = new DefaultAttack();
    block = new DefaultBlock();
    heal = new DefaultHeal();

    gummy_bear = bear;
}

// Destructor
Actions::~Actions()
{
    // Clean up the @class Object { Actions } by deleting the following memory
    delete attack;
    delete block;
    delete heal;

    delete gummy_bear;

    cout << "attack, block, & heal pointers successfully deleted" << endl;
}

// Accessors
double Actions::getAttackMultiplier(){ return attack_multiplier; }
double Actions::getSpecialAttackMultiplier(){ return special_attack_multiplier; }
double Actions::getDefenseMultiplier(){ return defense_multiplier; }
double Actions::getSpecialDefenseMulitplier(){ return special_defense_multiplier; }

GummyBear* Actions::getGummyBear(){ return gummy_bear; }

char Actions::getAttackType(){ return this->attack_type; }

Attack* Actions::getAttack(){ return this->attack; } 
Block*  Actions::getBlock(){ return this->block; }
Heal*   Actions::getHeal(){ return this->heal; } 


// Mutators
void Actions::setAttackMultiplier(double am_){ attack_multiplier = am_; }
void Actions::setSpecialAttackMultiplier(double sam_){ special_attack_multiplier = sam_; }
void Actions::setDefenseMultiplier(double dm_){ defense_multiplier = dm_; }
void Actions::setSpecialDefenseMultiplier(double sdm_){ special_defense_multiplier = sdm_; }

void Actions::setAttack(Attack* attack){ this->attack = attack; }
void Actions::setBlock(Block* block){ this->block = block; }
void Actions::setHeal(Heal* heal){ this->heal = heal; }