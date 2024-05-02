// Main file for software, this is where the program lives

// Import class modules for the program 
#include "src/Actions.h"
#include "src/GameEntities.h"
#include "src/UI.h"
#include "src/MemorySystem.h"
#include "src/RNG.h"

// Include other needed modules
#define NOMINMAX
#include <iostream>
#include <string>
#include <exception>
#include <iomanip>
#include <vector>
#include <limits>
#include <random>   // Used to set RNG game mechanics 
#include <thread>  //  These two modules are used for,
#include <chrono> //   handling the internal clock for the program

using namespace std;

/* Functions implemented to handled main game loop mechanics */

// Helper function for Colosseum
void executeAction(Actions& firstActor, Actions& secondActor, int firstMove, int secondMove, GummyBear& firstGummy, GummyBear& secondGummy) 
{
    bool firstBlocked = false, secondBlocked = false;
    if(firstMove == 2) {  // First actor attempts to block
        firstBlocked = firstActor.getBlock()->block(firstActor);
        cout << firstGummy.getBearName() << " attempts to block." << endl;
    }
    if(secondMove == 2) {  // Second actor attempts to block
        secondBlocked = secondActor.getBlock()->block(secondActor);
        cout << secondGummy.getBearName() << " attempts to block." << endl;
    }

    if(firstMove == 1 && !secondBlocked) {  // First actor attacks if second didn't successfully block
        firstActor.getAttack()->attack(firstActor, secondActor, firstActor.getAttackType() == 'P' ? firstActor.getAttackMultiplier(): firstActor.getSpecialAttackMultiplier(), firstActor.getAttackType());
    } else if(firstMove == 3) {  // First actor heals
        if(firstGummy.getCurrentHealth() > 0) {
            firstActor.getHeal()->heal(firstActor);
            cout << firstGummy.getBearName() << " heals." << endl;
        } else {
            cout << firstGummy.getBearName() << " cannot heal because they are defeated." << endl;
        }
    }

    if(secondMove == 1 && !firstBlocked) {  // Second actor attacks if first didn't successfully block
        secondActor.getAttack()->attack(secondActor, firstActor, 'P', secondActor.getAttackMultiplier());
    } else if(secondMove == 3) {  // Second actor heals
        if(secondGummy.getCurrentHealth() > 0) {
            secondActor.getHeal()->heal(secondActor);
            cout << secondGummy.getBearName() << " heals." << endl;
        } else {
            cout << secondGummy.getBearName() << " cannot heal because they are defeated." << endl;
        }
    }
}


// Function used to init the fight's 
void Colosseum(GummyBear* user, Cache* cache, UI ui)
{
    // Define User Actions & RNG system
    Actions user_actions(user);
    RNG     game_session_rng;

    // User condition
    bool user_defeated  = false;

    // This is why you're here the actual game loop
    // Continue the game until user faints
    while(user->getCurrentHealth() > 0 && !user_defeated)
    {   
        // Generate a wave of enemy gummies to a DYNAMIC VECTOR
        vector<GummyBear*> current_wave = game_session_rng.spawnWave(user->getStats().getLevel());
        std::cout << "Wave " << game_session_rng.getWaveNumber() << " Start!" << endl;

        // Loop through each one fighting off the wave
        for(auto it = current_wave.begin(); it != current_wave.end();)
        {
            // Declare variables used for each battle
            GummyBear* current_opponent = *it;
            Actions    opponent_actions(current_opponent);
            
            // Promp Battle 
            std::cout << user->getBearName() << " vs " << current_opponent->getBearName() << endl;
            user->PrintStats();
            std::cout << endl;
            current_opponent->PrintStats();

            // Load game stats and await 3 seconds before deleting it
            this_thread::sleep_for(chrono::seconds(3));
            ui.LineDelete(11);

            // Enemy condition
            bool enemy_defeated = false;

            std::cout << user->getBearName() << ": " << user->getCurrentHealth() << "/" << user->getStats().getHealth() << endl;
            std::cout << current_opponent->getBearName() << ": " << current_opponent->getCurrentHealth() << "/" << current_opponent->getStats().getHealth() << endl;

            // While both entities are alive
            while(!enemy_defeated && !user_defeated)
            {   

                // Get NPC & Player moves
                int npc_move = game_session_rng.evaluateMove(current_opponent, user->getStats().getLevel());
                int player_move = game_session_rng.evaluateMove();

                // Action Flow Module
                // Display stats per itertation
                cout << user->getBearName() << ": " << user->getCurrentHealth() << "/" << user->getStats().getHealth() << " HP" << endl;
                cout << current_opponent->getBearName() << ": " << current_opponent->getCurrentHealth() << "/" << current_opponent->getStats().getHealth() << " HP" << endl;

                // Execute actions based on speed and the actions chosen
                if(user->getStats().getSpeed() >= current_opponent->getStats().getSpeed()) 
                {
                    // User is faster or speed is tied
                    executeAction(user_actions, opponent_actions, player_move, npc_move, *user, *current_opponent);
                } 
                else 
                {
                    // NPC is faster
                    executeAction(opponent_actions, user_actions, npc_move, player_move, *current_opponent, *user);
                }

                // Check battle results
                enemy_defeated = current_opponent->getCurrentHealth() <= 0;
                user_defeated = user->getCurrentHealth() <= 0;

                // Enemy fainted
                if(enemy_defeated)
                {
                    // Reward xp & update user's level if applicable
                    int xp_gained = game_session_rng.getXP(current_opponent);
                    cache->setXp(cache->getXp() + xp_gained);
                    int cur_level = user->getStats().getLevel();

                    int set_level = cache->checkLevelUp(cur_level);
                    user->getStats().setLevel(set_level);
                    
                    // Award sugar if applicable
                    int sugar_awarded = set_level - cur_level;
                    cache->setSugarAmount(cache->getSugarAmount() + sugar_awarded);

                    cout << "XP gained " << xp_gained << endl;
                    cache->SaveGameProgress(user);
                    
                    // Handle memory of dynamic variables 
                    cout << current_opponent->getBearName() << " Defeated!" << endl;   
                    it++;
                }
            }

            // If defeated deleted allocated memory & break loop again
            if(user_defeated) 
            {
                cout << "Game Over: " << user->getBearName() << " is defeated womp womp!" << endl; 
                break;
            }
        }
        if(!user_defeated)
        {
            // Continue to next wave
            cout << "All enemies in wave have been dealt with!" << endl;
            cout << "Next wave ... " << endl;
            ui.LineDelete(6);
            cout << endl << endl;

            game_session_rng.increaseWaveNumber();

            current_wave.clear();
            this_thread::sleep_for(chrono::seconds(2));
        }
        else
        {
            cout << "User has been defeated, womp womp!" << endl;
            // Deallocate memory from dynamic vector
            current_wave.clear();
        }
    }
}


// Function used to train user's gummy
void Train(GummyBear* user, int sugar_amount, char gummy_type, UI& ui)
{
    // Training prompt init
    std::cout << "Welcome to the Sweet Baracks!" << endl;
    ui.LoadTemplate(ui.getBearUiPath());
    std::cout << endl;
    std::cout << "Woah! Your gummy is " << gummy_type << " type!" << endl;


    // Training session stat improvements
    int health_increase          = 5;
    int attack_increase          = 3;
    int defense_increase         = 2;
    int special_attack_increase  = 3;
    int special_defense_increase = 2;
    int speed_increase           = 3;

    // Based on gummy type you can get different training boosts
    switch (gummy_type) {
    case 'Q': 
        // Quantum type training attributes
        std::cout << "Quantum type gummies get 2x training on special attack & speed!" << endl;
        special_attack_increase *= 2;
        speed_increase          *= 2;
        break;
    
    case 'B': 
        // Brute type training attributes
        std::cout << "Brute type gummies get 2x training on health & attack!" << endl;
        health_increase *= 2;
        attack_increase *= 2;
        break;

    case 'M': 
        // MultiColor type training attributes
        std::cout << "MultiColor type gummies get 2x training on defense & special defense!" << endl;
        defense_increase         *= 2;
        special_defense_increase *=2;
        break;
    
    default: // Null
        break;
    }
    
    // Update gummy stats based on training
    Stats current_stats = user->getStats();
    current_stats.setHealth(current_stats.getHealth() + health_increase); 
    current_stats.setHealth(current_stats.getHealth() + health_increase);
    current_stats.setAttack(current_stats.getAttack() + attack_increase);
    current_stats.setDefense(current_stats.getDefense() + defense_increase);
    current_stats.setSpecialAttack(current_stats.getSpecialAttack() + special_attack_increase);
    current_stats.setSpecialDefense(current_stats.getSpecialDefense() + special_defense_increase);
    current_stats.setSpeed(current_stats.getSpeed() + speed_increase);
    
    user->setStats(current_stats); // Update gummy's stats

    // Await 3 seconds to display new stats
    std::cout << "Training complete!" << endl;
    user->PrintStats();
    this_thread::sleep_for(chrono::seconds(3));

    // Render Main menu
    ui.ClearScreen();
    ui.LoadTemplate(ui.getMainMenuUiPath());
}



// Main function to init the program 
int main()
{
    // Begin Program with needed objects of @class { Ui & Cache }
    UI ui_designs;            // Utilized to render game interfaces
    Cache game_cache_system; // Utilized to handle current game data

    // Utilized for battle memory
    Cache* cache_route = &game_cache_system;

    /* Init the game through welcome message interface */
    ui_designs.LoadTemplate(ui_designs.getWelcomeUiPath()); // Renders the welcome message 
    this_thread::sleep_for(chrono::seconds(2)); // Await 2 seconds of the welcome message
    ui_designs.ClearScreen(); // Clear the screen for next interface

    /* Next we render the game file interface & load a new or existing game */
    ui_designs.LoadTemplate(ui_designs.getLoadGameUiPath());
    
    // Pointer to User's Gummy Bear
    GummyBear* user_gummy_bear;

    // Validate whether the user is new or not
    bool is_new_game = game_cache_system.is_new_game();

    if(is_new_game) // Create new user game file if new game
    {
        // Prompt user to set up a new profile
        std::cout << endl << "Welcome to the world of gummy bears! Let's get started!" << endl;
        this_thread::sleep_for(chrono::seconds(2));

        // Render new user interface
        ui_designs.ClearScreen();
        ui_designs.LoadTemplate(ui_designs.getNewGameUiPath()); 

        // User defines new game file
        user_gummy_bear = game_cache_system.NewGame();
        user_gummy_bear->setBearName(game_cache_system.getGummyName()); 
        game_cache_system.SaveGameProgress(user_gummy_bear);
        ui_designs.ClearScreen();
    }
    else // Load existing user's game file
    {
        // Welcome user back & render their gummy
        user_gummy_bear = game_cache_system.LoadGame(); // Load user's gummy into game session

        std::cout << endl << "Welcome back " << user_gummy_bear->getBearName() << "! The world awaits." << endl;
        this_thread::sleep_for(chrono::seconds(2));

        ui_designs.ClearScreen(); 
    }

    // Render main menu
    ui_designs.LoadTemplate(ui_designs.getMainMenuUiPath());

    int menu_option = 0; // Holds user's menu choices

    // Menu system handles main game loop below 
    while(menu_option != 4) // option 4 = quit 
    {
        /* Main Game Loop */
        std::cout << "Selection: ";
        cin >> menu_option;

        if(cin.fail()) // User provided incorrect input type
        {
            cin.clear();
            cin.ignore(); // Ignore the bad input
            cout << "Invalid input type. Please enter a number." << endl;
        }
        else
        {
            cin.ignore(); // Incase any extra buffer

            switch (menu_option) {
                case 1:
                {
                    // Colosseum Mode

                    // Create access to memory system for in game memory access 

                    // Init the dialog before the battle starts, then update the current interface
                    std::cout << "Fend off swarms of gummy bears & bosses until death!" << endl;
                    std::cout << "Loading Colosseum ..." << endl;

                    this_thread::sleep_for(chrono::seconds(2));
                    ui_designs.ClearScreen();
                    ui_designs.LoadTemplate(ui_designs.getGummyBearUiPath());

                    // Init the battle loop
                    Colosseum(user_gummy_bear, cache_route, ui_designs); // Init Colosseum Mode

                    // Save game session after each Colosseum event
                    std::cout << "Saving game file .... " << endl;
                    game_cache_system.SaveGameProgress(user_gummy_bear);
                    this_thread::sleep_for(chrono::seconds(2));
                    std::cout << "Game file saved sucessfully!" << endl;

                    // Render Main Menu
                    ui_designs.ClearScreen();
                    ui_designs.LoadTemplate(ui_designs.getMainMenuUiPath());
                    break;
                }

                case 2:
                {
                    // Train Mode
                    // Check for funding first
                    if(game_cache_system.getSugarAmount() <= 0) std::cout << "Insufficient funds, go lock in!" << endl;
                    else 
                    {
                        // Init Training
                        // Training sessions cost 1 sugar each
                        game_cache_system.setSugarAmount(game_cache_system.getSugarAmount() - 1);

                        // Train Gummy Bear
                        Train(user_gummy_bear, game_cache_system.getSugarAmount(), user_gummy_bear->getStats().getBearType(), ui_designs);
                    }
                    break;
                }

                case 3:
                {
                    // Save
                    std::cout << "Saving session ..." << endl;
                    game_cache_system.SaveGameProgress(user_gummy_bear);
                    std::cout << "Session was saved sucessfully!" << endl;
                    break;
                } 

                case 4: 
                {
                    // Quit
                    std::cout << "Your adventure awaits!" << endl;
                    break;
                }
                
                default:
                    std::cout << "Error: Invalid selection " << menu_option << " try again." << endl;
                    break;
            }
        }
    }
    // End of game loop

    // Before game ends assure game is saved & pointer memory is deallocated
    game_cache_system.SaveGameProgress(user_gummy_bear);
    delete user_gummy_bear;
    // Deallocate cache_route memory 
    delete cache_route;
    return 0;
}