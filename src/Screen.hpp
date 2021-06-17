#ifndef WILDCARD_SCREEN_HPP
#define WILDCARD_SCREEN_HPP
#include "GameEngine.hpp"
/**
 * Fully abstract class of Screen
 * All methods are overriden by GameScreen, MenuScreen or FileScreen
 */
class Screen {
public:
    GameEngine & game_engine;
    /**
     * Copies game_engine to a local one
     * @param game_engine copied instance of game_engine
     */
    explicit Screen(GameEngine & game_engine);
    /**
     * Initializes screen
     * Sets up the size of terminal
     */
    virtual void Initialize() = 0;
    /**
     * Updates all variables
     * Waits for key input
     */
    virtual void Update() = 0;
    /**
     * Draws everything to the terminal
     */
    virtual void Draw() = 0;
    /**
     * Deletes instance of Screen
     */
    virtual ~Screen() = 0;
};
#endif //WILDCARD_SCREEN_HPP
