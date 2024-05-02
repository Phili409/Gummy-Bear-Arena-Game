// UI.h 
// Declaration File
// Classes here are utilized to manage the terminal's display throughout the program's cycle

#ifndef UI_H
#define UI_H

// Imported Modules used for this class
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// Declare @class { UI }
class UI {
private:
    string const main_menu_ui_path  = "Assets\\MainMenu.txt";           // Path to file template for main menu interface
    string const new_game_ui_path   = "Assets\\CreateNewGame.txt";     // Path to file template for new game interface 
    string const load_game_ui_path  = "Assets\\LoadGame.txt";         // Path to file template for saved files interface 
    string const gummy_bear_ui_path = "Assets\\GummyBear.txt";       //  Path to file template for gummy bear fight interface 
    string const welcome_ui_path    = "Assets\\WelcomeMessage.txt"; // Path to file template for welcome to the game interface 
    string const bear_ui_path       = "Assets\\Bear.txt";          // Path to file template for bear mascot interface

public:
    // Constructor
    UI();

    // Accessors
    string getMainMenuUiPath() const;     // Returns { main_menu_ui_path } private member @var
    string getNewGameUiPath() const;     // Returns { new_game_ui_path } private member @var
    string getLoadGameUiPath() const;   // Returns { load_game_ui_path } private member @var
    string getGummyBearUiPath() const; // Returns { gummy_bear_ui_path } private member @var
    string getWelcomeUiPath() const;  // Returns { welcome_ui_path } private member @var
    string getBearUiPath() const;    // Returns { bear_ui_path } private member @var
    // File Paths are const thus no need for mutators

    // Member Functions
    void LoadTemplate(string); 

    void ClearScreen();

    void LineDelete(int);

};
#endif