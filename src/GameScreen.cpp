#include "GameScreen.hpp"

GameScreen::GameScreen(GameEngine &game_engine, bool second_player, bool new_game, const string & path)
 :  Screen(game_engine),
    config(game_engine.GetConfiguration())
{
    game_window = nullptr;
    details_window = nullptr;
    def_window = nullptr;
    max_row = 0;
    max_col = 0;
    can_use_card = true;
    AI = !second_player;
    current_player_AI = false;
    bool wrong_read = false;
    if(new_game) {
        if(!config.ReadConfigFile(path)) {
            wrong_read = true;
            PrintErrorScreen();
            game_engine.SetExit();
        }
        else
            ConfigureGame(second_player);
        current_player = 0;
    }
    else {
        if(!config.ReadSavedFile(path)) {
            wrong_read = true;
            PrintErrorScreen();
            game_engine.SetExit();
        }
        else {
            players = config.CopyPlayers();
            current_player = config.GetCurrentPlayer();
            AI = config.GetAI();
            if(current_player == 1 && AI)
                current_player_AI = true;
        }
    }
    if(!wrong_read) {
        for (auto n : players)
            n->SetMaxCards(config.GetMaxCards());
        players[current_player]->AddCard(config.ReturnRandomCard());
    }
    if(current_player_AI)
        game_engine.SetNoInput();
}

void GameScreen::Initialize() {
    getmaxyx(stdscr, max_row, max_col);
    max_row /= 2;
    max_col /= 2;
    game_window = newwin(max_row, max_col, 0, 0);
    details_window = newwin(max_row, max_col/2, 0, max_col);
    def_window = newwin(max_row, max_col, 0, 0);
    CheckSize();
    curs_set(0);
    players[current_player]->SumCards();
}

void GameScreen::Update() {
    can_use_card = true;
    unsigned int current_amount;
    players[current_player]->SetAmountCards(players[!current_player]->GetCards().size());
    switch(players[current_player]->NextAction(game_engine.GetKey())) {
        case(GAME_QUIT) :
            game_engine.SetExit();
            break;
        case(GAME_SAVE) :
            config.SaveFile(players, !current_player, AI);
            game_engine.SetExit();
            break;
        case(GAME_USE_CARD) :
            current_amount = players[current_player]->GetCards().size();
            if (current_amount != 0)
                can_use_card = players[current_player]->PickCard()->UseCard(*(players[current_player]), *(players[!current_player]));
            if (players[!current_player]->GetHealth() <= 0) {
                WinnerScreen();
            }
            if (current_amount != players[current_player]->GetCards().size() &&
                players[current_player]->GetCursor() + 1 > players[current_player]->GetCards().size())
                players[current_player]->ShiftCursor();
            break;
        case(GAME_NEXT_ROUND) :
            if(AI) {
                current_player_AI = !current_player_AI;
                if (current_player_AI)
                    game_engine.SetNoInput();
                else
                    game_engine.SetInput();
            }
            if(AI && current_player == 1)
                PrintYourTurnScreen();
            else if(!AI)
                PrintWaitScreen();
            NextPlayer();
            break;
    }
    players[current_player]->SumCards();
}

void GameScreen::Draw() {
    players[current_player]->DrawCards(game_window, current_player, max_row);
    players[current_player]->DrawInfo(details_window, max_col, max_row);
    string text_header = "DETAIL HRACU";
    string text_health = "POCET ZIVOTU";
    string text_player1 = "HRAC 1: ";
    string text_player2 = "HRAC 2: ";
    mvwaddstr(details_window, 6, max_col / 4 - (text_header.size() / 2), text_header.c_str());
    mvwaddstr(details_window, 7, 2, text_health.c_str());
    mvwaddstr(details_window, 8, 2, text_player1.c_str());
    mvwaddstr(details_window, 8, text_player1.size() + 2, to_string(players[0]->GetHealth()).c_str());
    mvwaddstr(details_window, 9, 2, text_player2.c_str());
    mvwaddstr(details_window, 9, text_player2.size() + 2, to_string(players[1]->GetHealth()).c_str());
    mvwaddstr(details_window, 14, 2, ("POCET KARET V RUCE SOUPERE: " + to_string(players[!current_player]->GetCards().size())).c_str());
    if(!can_use_card)
        mvwaddstr(game_window, 12, 2, "NELZE POUZIT KARTU");
    wrefresh(game_window);
    wrefresh(details_window);
}

void GameScreen::NextPlayer() {
    players[!current_player]->AddCard(config.ReturnRandomCard());
    players[current_player]->SetCursor();
    SwitchPlayer();
}

void GameScreen::SwitchPlayer() {
    current_player = !current_player;
}

void GameScreen::ConfigureGame(bool second_player) {
    players.push_back(new Player(config.GetHealth(), config.GetHealth()));
    if (second_player)
        players.push_back(new Player(config.GetHealth(), config.GetHealth()));
    else
        players.push_back(new PlayerAI(config.GetHealth(), config.GetHealth()));
    for(auto n : players) {
        n->SetMaxCards(config.GetMaxCards());
        for(unsigned int i = 0; i < config.GetMaxCards(); i++) {
            Card * new_card = config.ReturnRandomCard();
            if(new_card != nullptr)
                n->AddCard(config.ReturnRandomCard());
        }
    }
}

void GameScreen::PrintWaitScreen() {
    clear();
    refresh();
    box(def_window, 0, 0);
    string text_player = "NA RADE JE HRAC " + to_string(!current_player+1);
    mvwaddstr(def_window, 2, 2, text_player.c_str());
    mvwaddstr(def_window, 4, 2, "STISKNETE LIBOVOLNOU KLAVESU");
    wrefresh(def_window);
    getch();
}

void GameScreen::CheckSize() {
    if(max_row*2 < MIN_ROW || max_col*2 < MIN_COL) {
        box(game_window, 0, 0);
        mvwaddstr(game_window, 2, 2, "PRILIS MALY TERMINAL");
        wrefresh(game_window);
        getch();
        game_engine.SetExit();
    }
}

void GameScreen::WinnerScreen() {
    clear();
    refresh();
    wmove(def_window, 1, 0);
    wclrtoeol(def_window);
    box(def_window, 0, 0);
    if(current_player == 1 && AI)
        mvwaddstr(def_window, 2, 2, "PROHRA! POCITAC VYHRAL :(");
    else if(current_player == 0 && AI)
        mvwaddstr(def_window, 2, 2, "VYHRA! POCITAC BYL PORAZEN :)");
    else {
        string text_winner = "VITEZEM JE HRAC " + to_string(current_player + 1);
        mvwaddstr(def_window, 2, 2, text_winner.c_str());
    }
    mvwaddstr(def_window, 4, 2, "STISKNETE LIBOVOLNOU KLAVESU");
    wrefresh(def_window);
    getch();
    game_engine.SetExit();
}

void GameScreen::PrintErrorScreen() {
    clear();
    refresh();
    if(def_window != nullptr)
        delwin(def_window);
    getmaxyx(stdscr, max_row, max_col);
    def_window = newwin(max_row/2, max_col/2, 0, 0);
    box(def_window, 0, 0);
    mvwaddstr(def_window, 1, 2, "SPATNY FORMAT KONFIGURACNIHO SOUBORU :(");
    wrefresh(def_window);
    getch();
}

void GameScreen::PrintYourTurnScreen() {
    clear();
    refresh();
    box(def_window, 0, 0);
    mvwaddstr(def_window, 1, 2, "JSI NA RADE!");
    wrefresh(def_window);
    getch();
}

GameScreen::~GameScreen() {
    delwin(game_window);
    delwin(details_window);
    delwin(def_window);
    for(auto n : players) {
        delete n;
    }
}