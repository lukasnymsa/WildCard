#include "FileScreen.hpp"
#define SAVES "saves"
#define CONFIG "config"
#define EXAMPLES "examples"
#define K_QUIT 'q'
#define K_SWITCH 's'
#define K_RELOAD 'r'

FileScreen::FileScreen(GameEngine &game_engine, int type)
 :  Screen(game_engine)
{
    file_window = nullptr;
    max_row = 0;
    max_col = 0;
    side = 0;
    switch_path = false;
    this->type = type;
    cursor_position = 0;
    fs::create_directory("saves");
    fs::create_directory("config");
}

void FileScreen::Initialize() {
    getmaxyx(stdscr, max_row, max_col);
    file_window = newwin(max_row/2, max_col/2, 0, 0);
    curs_set(0);
    if(type == GAME_LOAD_NEW)
        path = SAVES;
    else
        path = CONFIG;
    if(switch_path)
        path = EXAMPLES;
    if(fs::is_directory(path))
        for (const auto &entry : fs::directory_iterator(path))
            files.push_back(entry.path());
    else
        game_engine.SetExit();
}

void FileScreen::Update() {
    switch(game_engine.GetKey()) {
        case K_QUIT :
            game_engine.SwitchScreen(new MenuScreen(game_engine));
            break;
        case K_SWITCH :
            files.clear();
            delwin(file_window);
            cursor_position = 0;
            switch_path = !switch_path;
            side = 0;
            Initialize();
            break;
        case K_RELOAD :
            files.clear();
            delwin(file_window);
            cursor_position = 0;
            side = 0;
            Initialize();
            break;
        case KEY_UP :
            if(cursor_position != 0 && cursor_position != side*MAX_LINES_TO_PRINT && cursor_position != MAX_LINES_TO_PRINT  && !files.empty())
                cursor_position--;
            break;
        case KEY_DOWN :
            if(cursor_position != files.size()-1 && cursor_position != side*MAX_LINES_TO_PRINT+(MAX_LINES_TO_PRINT-1)
                                    && cursor_position != (MAX_LINES_TO_PRINT-1) && !files.empty() && !files.empty())
                cursor_position++;
            break;
        case KEY_LEFT :
            if(side != 0 && !files.empty()) {
                side--;
                cursor_position = side * MAX_LINES_TO_PRINT;
            }
            break;
        case KEY_RIGHT :
            if((side * MAX_LINES_TO_PRINT + MAX_LINES_TO_PRINT) < files.size()  && !files.empty()) {
                side++;
                cursor_position = side * MAX_LINES_TO_PRINT;
            }
            break;
        case K_ENTER :
            if(files.empty())
                break;
            if(type == GAME_VS_PLAYER)
                game_engine.SwitchScreen(new GameScreen(game_engine, true, true, files[cursor_position]));
            else if(type == GAME_VS_AI)
                game_engine.SwitchScreen(new GameScreen(game_engine, false, true, files[cursor_position]));
            else if(type == GAME_LOAD_NEW)
                game_engine.SwitchScreen(new GameScreen(game_engine, false, false, files[cursor_position]));
            break;
    }
}

void FileScreen::Draw() {
    ClearWindow(file_window);
    box(file_window, 0, 0);
    mvwaddstr(file_window, 1, 2, ("VYBER SOUBOR Z: " + path).c_str());
    string format;
    int row = 3;
    for(size_t i = side*MAX_LINES_TO_PRINT; (i < files.size()) && (i < side*MAX_LINES_TO_PRINT+MAX_LINES_TO_PRINT); i++) {
        format = cursor_position == i ? files[i] + "  <=" : files[i];
        if(path == SAVES)
            format.erase(0,6);
        else if(path == CONFIG)
            format.erase(0,7);
        else
            format.erase(0,9);
        mvwaddstr(file_window, row, 2, format.c_str());
        row++;
    }
    if(!files.empty()) {
        string arrow_left;
        string arrow_right;
        if(side != 0)
            arrow_left = "< ";
        if(side != files.size()/MAX_LINES_TO_PRINT && files.size() > MAX_LINES_TO_PRINT)
            arrow_right = " >";
        string text_side = "SOUBOR: " + arrow_left + to_string(cursor_position + 1) + '/' + to_string(files.size()) + arrow_right;
        mvwaddstr(file_window, 9, 2, text_side.c_str());
    }
    if(files.empty()) {
        if(path == SAVES)
            mvwaddstr(file_window, 3, 2, "ZADNE ULOZENE HRY");
        else
            mvwaddstr(file_window, 3, 2, "SLOZKA JE PRAZDNA -> PRIDEJ KONFIGURACNI SOUBOR DO SLOZKY");
    }
    mvwaddstr(file_window, 11, 2, "'s' - do/z testovaci slozky");
    mvwaddstr(file_window, 12, 2, "'r' - refreshnout stranku");
    mvwaddstr(file_window, 13, 2, "'q' - zpet do menu");
    wrefresh(file_window);
}

FileScreen::~FileScreen() {
    delwin(file_window);
}

void FileScreen::ClearWindow(WINDOW * screen) {
    int row = max_row;
    wmove(screen, 1, 0);
    for(int i = 2; i <= row + 2; i++) {
        wclrtoeol(screen);
        wmove(screen, i, 0);
    }
}