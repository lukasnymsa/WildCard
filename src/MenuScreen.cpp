#include "MenuScreen.hpp"
#define EXIT 3


MenuScreen::MenuScreen(GameEngine &game_engine): Screen(game_engine)
{
    menu_options = {"NOVA HRA PROTI HRACI", "NOVA HRA PROTI POCITACI", "HRAT ULOZENOU HRU", "KONEC"};
    menu_window = nullptr;
    path_window = nullptr;
    column = 2;
    cursor_position = 0;
    key = ERR;
    max_row = 0;
    max_col = 0;
}

void MenuScreen::Initialize() {
    getmaxyx(stdscr, max_row, max_col);
    menu_window = newwin(max_row/2, max_col/2, 0, 0);
    path_window = newwin(max_row/2, max_col/2, 0, 0);
    curs_set(0);
    CheckSize();
    Draw();
}

void MenuScreen::Update() {
    key = game_engine.GetKey();
    switch(key) {
        case KEY_UP :
            if (cursor_position != 0)
                cursor_position--;
            break;
        case KEY_DOWN :
            if(cursor_position != menu_options.size() - 1)
                cursor_position++;
            break;
        case K_ENTER :
            SwitchScreen();
            break;
    }
}

void MenuScreen::Draw() {
    ClearWindow(menu_window);
    int row = 2;
    box(menu_window, 0, 0);
    for(size_t i = 0; i < menu_options.size(); i++) {
        string format = cursor_position == i ? menu_options[i] + "  <=" : menu_options[i];
        mvwaddstr(menu_window, row, column, format.c_str());
        row++;
    }
    wrefresh(menu_window);
}

MenuScreen::~MenuScreen() {
    delwin(menu_window);
    delwin(path_window);
}

void MenuScreen::ClearWindow(WINDOW * screen) {
    int row = menu_options.size();
    wmove(screen, 1, 0);
    for(int i = 2; i <= row + 2; i++) {
        wclrtoeol(screen);
        wmove(screen, i, 0);
    }
}

void MenuScreen::SwitchScreen() {
    switch(cursor_position) {
        case GAME_VS_PLAYER:
            game_engine.SwitchScreen(new FileScreen(game_engine, GAME_VS_PLAYER));
            break;
        case GAME_VS_AI:
            game_engine.SwitchScreen(new FileScreen(game_engine, GAME_VS_AI));
            break;
        case GAME_LOAD_NEW:
            game_engine.SwitchScreen(new FileScreen(game_engine, GAME_LOAD_NEW));
            break;
        case EXIT:
            game_engine.SetExit();
            break;
    }
}

void MenuScreen::CheckSize() {
    if(max_row < MIN_ROW || max_col < MIN_COL) {
        box(menu_window, 0, 0);
        mvwaddstr(menu_window, 2, 2, "PRILIS MALY TERMINAL");
        wrefresh(menu_window);
        getch();
        game_engine.SetExit();
    }
}