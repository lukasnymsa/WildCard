#include "GameEngine.hpp"
#include "MenuScreen.hpp"
#include "GameConfig.hpp"
#include <curses.h>

using namespace std;

GameEngine::GameEngine()
:
    run_state(false),
    pressed_key(ERR),
    AI_input(false),
    screen(nullptr),
    configuration()
{ }

GameEngine::~GameEngine() {
    delete screen;
    endwin();
}

void GameEngine::Start() {
    run_state = true;
}

bool GameEngine::RunState() const {
    return run_state;
}

void GameEngine::Update() {
    if(!run_state)
        return;
    if(!AI_input)
        pressed_key = getch();
    screen->Update();
}

void GameEngine::Draw() {
    if(!run_state)
        return;
    screen->Draw();
}

void GameEngine::SwitchScreen(Screen *new_screen) {
    delete screen;
    clear();
    refresh();
    screen = new_screen;
    if(!run_state)
        return;
    screen->Initialize();
}

int GameEngine::GetKey() const {
    return pressed_key;
}

void GameEngine::SetExit() {
    run_state = false;
}

void GameEngine::SetNoInput() {
    AI_input = true;
}

void GameEngine::SetInput() {
    AI_input = false;
}

GameConfig & GameEngine::GetConfiguration() {
    return configuration;
}