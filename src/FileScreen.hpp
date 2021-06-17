#ifndef WILDCARD_FILESCREEN_HPP
#define WILDCARD_FILESCREEN_HPP

#include "Screen.hpp"
#include "GameScreen.hpp"
#include "MenuScreen.hpp"
#include "Constants.hpp"
#include <filesystem>

class MenuScreen;
namespace fs = std::filesystem;

/**
 * Represents screen with all config and save files
 * User chooses which file to open and use
 */
class FileScreen : public Screen {
public:
    /**
     * Copies game_engine to a local one
     * @param game_engine copied instance of game_engine
     * @param type decides which folder to open
     */
    FileScreen(GameEngine & game_engine, int type);
    /**
     * Initializes screen
     * Sets up the size of terminal
     * Creates new instance of file_window
     * Initializes the vector of all files found in selected folder
     */
    void Initialize() override;
    /**
     * Waits for key input
     * Changes local variables
     */
    void Update() override;
    /**
     * Draws all files to the screen and other needed information
     */
    void Draw() override;
    /**
     * Deletes instance of FileScreen
     */
    ~FileScreen() override;
private:
    WINDOW * file_window;
    void ClearWindow(WINDOW * screen);
    int max_row;
    int max_col;
    int type;
    string path;
    bool switch_path;
    unsigned int side;
    unsigned int cursor_position;
    vector<string> files;
};

#endif //WILDCARD_FILESCREEN_HPP
