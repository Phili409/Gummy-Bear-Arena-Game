// Actions.h
// Declaration File 
// Utilized to declare

/*          Description         */
// Classes declared here are used for dynamic fighting between Gummies
// Where they can use the same @class Object { Actions } to determine the Gummie's attributes & moves in battle


// Init Declaration
#ifndef ACTIONS_H
#define ACTIONS_H


class Actions;
// Imported Modules used for this file 
#include <string>
#include <iostream>
#include "GameEntities.h" // Import GameEntities Module to access GummyBear Class

using namespace std; // Avoid repetitive use of std

/*  Declare Abstract @classes      */
/*  Used to create Dynamic Attacks */
class Attack {
public:
    virtual void attack(Actions& user, Actions& target, int attack_rate, char attack_type) const = 0; // Pure Virtual Function used as a placeholder for Attack Type determined in runtime
    virtual ~Attack(){} // Destructor
};

class Block{
public:
    virtual bool block(Actions& user) = 0; // Pure Virtual Function used as a placeholder for Block Type determined in runtime
    virtual ~Block(){}  // Destructor
};

class Heal{
public:
    virtual void heal(Actions& user) = 0; // Pure Virtual Function used as a placeholder for Heal Type determined in runtime
    virtual ~Heal(){}  // Destructor
};


/*  Declare Derived Classes for special & default attacks  */

// DEFAULT MOVES
class DefaultAttack: public Attack {
public:
    void attack(Actions& user, Actions& target, int attack_rate, char attack_type) const override; // Sets Attack Type -> Default 
};

class DefaultBlock:  public Block {
public:
    bool block(Actions& user) override;  // Sets Block Type -> Default
};

class DefaultHeal:  public Heal {
public:
    void heal(Actions& user) override; // Sets Heal Type -> Default
};


// SPECIAL MOVES
class ParticleBeam: public Attack // For Quantum Type Gummy Bear
{
public:
    void attack(Actions& user, Actions& target, int attack_rate, char attack_type) const override; // Sets Attack Type -> Special attack ONLY for Quantum Type GummyBear
};

class MudWall: public Block // For Brute Type Gummy Bear
{
    bool block(Actions& user) override; // Sets Block Type -> Special attack ONLY for Brute Type GummyBear
};

class DivinePotion: public Heal // For MultiColor Type Gummy Bear
{
    void heal(Actions& user) override; // Sets Heal Type -> Special attack ONLY for MultiColor Type GummyBear
};


/*  Declare @class Actions  */
class Actions
{
private: // Private Members (No outside access)
    double attack_multiplier;             // Store @var { attack_multiplier } boosts OR decays physical damage
    double special_attack_multiplier;    // Store @var { special_attack_multiplier } boosts OR decays special damage
    double defense_multiplier;          // Store @var { defense_multiplier } boosts OR decays physical defense
    double special_defense_multiplier; // Store @var { special_defense_multiplier } boosts OR decays special defense

    char attack_type; // Store @var { attack_type } which specifies if the Gummy is a physical OR special attacker | 'P' OR 'S'

    Attack *attack;  // Allows runtime polymorphism for { Attack } Type
    Block  *block;  // Allows runtime polymorphism for { Block } Type
    Heal   *heal;  // Allows runtime polymorphism for { Heal } Type

    GummyBear* gummy_bear; // Pointer to GummyBear Object that will be performing the actions

public: // Public Members
    // Constructor
    Actions(GummyBear*); // Based on the passed @param { GummyBear& } we use the object's value to determine which actions the GummyBear can take Dynamically in runtime

    // Destructor
    ~Actions(); // Avoids memory leaks by deleting Dynamic Memory from private members { attack, block, & heal } as well as { gummy_bear }

    // Accessor(s)
    double getAttackMultiplier();            // Returns { attack_multiplier } Private Member 
    double getSpecialAttackMultiplier();    // Returns { special_attack_multiplier } Private Member 
    double getDefenseMultiplier();         // Returns { defense_multiplier } Private Member 
    double getSpecialDefenseMulitplier(); // Returns { special_defense_multiplier } Private Member 

    char getAttackType(); // Returns { attack_type } private member 

    Attack* getAttack();  // Returns { attack } Private Member Reference  
    Block*  getBlock();   // Returns { block } Private Member Reference
    Heal*   getHeal();    // Returns { heal } Private Member Reference

    GummyBear* getGummyBear(); // Returns { gummy_bear } Private Member Reference

    // Mutator(s)
    void setAttackMultiplier(double);             // Updates the value of private member { attack_multiplier }
    void setSpecialAttackMultiplier(double);     // Updates the value of private member { special_attack_multiplier }  
    void setDefenseMultiplier(double);          // Updates the value of private member { defense_multiplier }
    void setSpecialDefenseMultiplier(double);  // Updates the value of private member { special_defense_multiplier }

    void setAttack(Attack*);  // Sets attack type through runtime polymorphism
    void setBlock(Block*);   // Sets block type through runtime polymorphism
    void setHeal(Heal*);    // Sets heal type through runtime polymorphism
};
#endif