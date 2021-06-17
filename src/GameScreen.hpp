#ifndef WILDCARD_GAMESCREEN_HPP
#define WILDCARD_GAMESCREEN_HPP
#include "Screen.hpp"
#include <curses.h>
#include "Card.hpp"
#include "Player.hpp"
#include "PlayerAI.hpp"
#include "MenuScreen.hpp"
#include "Constants.hpp"

class MenuScreen;

/**
 * Main class for the game
 * Includes all players in game
 * Checks end of the round or the whole game
 */
class GameScreen : public Screen {
public:
    /**
     * Sets up GameScreen
     * Loads configuration
     * @param game_engine copied instance of game_engine
     * @param second_player True if the second player is a player and not AI
     * @param new_game True if loading new game
     * @param path Path to the chosen config or save file
     */
    GameScreen(GameEngine & game_engine, bool second_player, bool new_game, const string & path);
    /**
     * Initializes screen
     */
    void Initialize() override;
    /**
     * Updates cards in hand of players
     * Checks if the game should end
     * Updates cursor position and pressed key
     */
    void Update() override;
    /**
     * Draws cards and needed info
     * Draws arrow to the current position of cursor
     */
    void Draw() override;
    /**
     * Deletes instance of GameScreen
     */
    ~GameScreen() override;
private:
    WINDOW * game_window;
    WINDOW * details_window;
    WINDOW * def_window;
    vector<Player*> players;
    int current_player;
    bool AI;
    bool current_player_AI;
    bool can_use_card;
    int max_row, max_col;
    GameConfig & config;
    void NextPlayer();
    void SwitchPlayer();
    void PrintWaitScreen();
    /**
     * Adds new players to the game and gives them cards
     * @param second_player False if the game is vs AI
     */
    void ConfigureGame(bool second_player);
    void CheckSize();
    void WinnerScreen();
    void PrintErrorScreen();
    void PrintYourTurnScreen();
};

#endif //WILDCARD_GAMESCREEN_HPP
