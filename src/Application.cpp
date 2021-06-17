#include "Application.hpp"

Application::Application() {
    gameEngine = new GameEngine();
}

bool Application::Run() const {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
    gameEngine->Start();
    gameEngine->SwitchScreen(new MenuScreen(*gameEngine));
    while(gameEngine->RunState()) {
        gameEngine->Update();
        gameEngine->Draw();
    }
    return false;
}

Application::~Application() {
    delete gameEngine;
}


