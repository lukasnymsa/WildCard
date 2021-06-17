#ifndef WILDCARD_APPLICATION_HPP
#define WILDCARD_APPLICATION_HPP
#include "curses.h"
#include "GameEngine.hpp"
#include "MenuScreen.hpp"
/**
 * The while loop of game is implemented in this class
 */
class Application {
public:
    /**
     * Creates new instance of Application
     */
    Application();
    /**
     * While loop of game
     * @return True if still running
     */
    bool Run() const;
    /**
     * Delete instance of Application
     */
    ~Application();
private:
    GameEngine * gameEngine;
};

#endif //WILDCARD_APPLICATION_HPP
