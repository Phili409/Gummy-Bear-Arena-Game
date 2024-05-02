// UI.cpp
// Definition File 

// Include needed modules for this file
#include "UI.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <windows.h>

using namespace std;


// Constructor is default always for @class { UI }
UI::UI(){} 

// Accessors
string UI::getMainMenuUiPath()  const { return this->main_menu_ui_path; }
string UI::getNewGameUiPath()   const { return this->new_game_ui_path; }
string UI::getLoadGameUiPath()  const { return this->load_game_ui_path; }
string UI::getGummyBearUiPath() const { return this->gummy_bear_ui_path; }
string UI::getWelcomeUiPath()   const { return this->welcome_ui_path; }
string UI::getBearUiPath()      const { return this->bear_ui_path; }

// Memeber Functions 

// Generates chosen interface
void UI::LoadTemplate(string file_path)
{
    ifstream template_file(file_path); // Attempt to open given template file 

    if (!template_file.is_open())
    {
        cout << "Error: Opening file " << file_path << endl;
    }

    string line; // Used to print template 
    while(getline(template_file, line)) // Until there are no more lines in the .txt file
    {
        cout << line << endl; // Print each line out
    }

    template_file.close(); // Close opened file
}

// Function to clear entire screen
void UI::ClearScreen()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  screen_coordiantes = { 0, 0 }; // Home Coordinates
    DWORD  char_count;
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cell_count;

    if(hStdOut == INVALID_HANDLE_VALUE)
    {
        cout << "Error: Invalid handle value" << endl;
        return;
    }

    // Get amount of cells in the current buffer 
    if(!GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        cout << "Error: Failed to get buffer info" << endl;
        return;
    }
    cell_count = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill Buffer with spaces
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cell_count, screen_coordiantes, &char_count))
    {
        cout << "Error: Failed to fill buffer with attributes" << endl;
        return;
    }

    // Fill buffer with current color & attributes
    if(!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cell_count, screen_coordiantes, &char_count))
    {
        cout << "Error: Failed to fill buffer with attributes" << endl;
        return;
    }
    
    // Change cursor to home coordinates
    SetConsoleCursorPosition(hStdOut, screen_coordiantes);
}

// Clears a specified amount of lines
void UI::LineDelete(int line_count)
{
    for(int i = 0; i < line_count; i++) cout << "\033[A\033[K";
}