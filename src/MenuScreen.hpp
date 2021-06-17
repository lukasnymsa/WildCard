#ifndef WILDCARD_MENUSCREEN_HPP
#define WILDCARD_MENUSCREEN_HPP
#include "Screen.hpp"
#include "GameScreen.hpp"
#include "FileScreen.hpp"
#include "Constants.hpp"
#include "curses.h"

/**
 * Represents screen of menu
 * Includes game vs player, game vs AI, load game and exit
 */
class MenuScreen : public Screen {
public:
    /**
     * Copies game_engine to a local one
     * Initializes menu_options with all possible choices
     * @param game_engine copied instance of game_engine
     */
    MenuScreen(GameEngine & game_engine);
    /**
     * Initializes screen
     */
    void Initialize() override;
    /**
     * Updates all variables
     * Waits for key input
     * Moves cursor
     */
    void Update() override;
    /**
     * Draws everything to the terminal
     * Draws arrow to the current position of cursor
     */
    void Draw() override;
    /**
     * Deletes instance of MenuScreen
     */
    ~MenuScreen() override;
private:
    vector<string> menu_options;
    WINDOW * menu_window;
    WINDOW * path_window;
    int column;
    unsigned int cursor_position;
    int key;
    int max_row;
    int max_col;
    void ClearWindow(WINDOW * menu_window);
    void SwitchScreen();
    void CheckSize();
};

#endif //WILDCARD_MENUSCREEN_HPP
