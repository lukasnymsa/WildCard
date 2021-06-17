#ifndef WILDCARD_GAMEENGINE_HPP
#define WILDCARD_GAMEENGINE_HPP
#include "GameConfig.hpp"
#include <vector>
#include <string>
class Screen;
/**
 * Represent the main class of whole project
 * Current screen and pressed key are stored
 */
class GameEngine {
public:
    /**
     * Sets run_state to false
     */
    explicit GameEngine();
    /**
     * Reads game configuration and sets it
     * Changes the runState to true
     */
    void Start();
    /**
     *
     * @return True if the engine is running
     */
    bool RunState() const;
    /**
     * Waits for input from keyboard
     * Then updates all data
     */
    void Update();
    /**
     * Draws everything including new updated data
     */
    void Draw();
    /**
     * Changes screen between GameScreen and MenuScreen
     * @param screen new screen which will be initialized
     */
    void SwitchScreen(Screen * screen);
    /**
     * Returns pressed key
     * @return pressed key
     */
    int GetKey() const;
    /**
     * Sets run_state to false
     */
    void SetExit();
    /**
     * Turns off waiting for input
     */
    void SetNoInput();
    /**
     * Turns on waiting for input
     */
    void SetInput();
    /**
     * @return complete configuration
     */
    GameConfig & GetConfiguration();
    /**
     * Deletes instance of GameEngine
     */
    ~GameEngine();
private:
    bool run_state;
    int  pressed_key;
    bool AI_input;
    Screen * screen;
    GameConfig configuration;
};
#endif //WILDCARD_GAMEENGINE_HPP
