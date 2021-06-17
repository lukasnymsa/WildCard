#include "PlayerAI.hpp"
#define THROW_CARD 4;

int PlayerAI::NextAction(int key_input) {
    int position = 0;
    for(auto n : cards_hand) {
        if(n->GetType() == ATT_CARD) { // attack card
            cursor_position = position;
            return GAME_USE_CARD;
        }
        if(health != max_health && n->GetType() == HEAL_CARD) {
            cursor_position = position;
            return GAME_USE_CARD;
        }
        if(n->GetType() == TAKE_CARD && enemy_cards >= 1) {
            cursor_position = position;
            return GAME_USE_CARD;
        }
        position++;
    }
    if(cards_hand.size() >= max_cards) {
        ThrowCard();
        if(!cards_hand.empty())
            cards_hand.erase(cards_hand.begin() + cursor_position);
        return THROW_CARD;
    }
    return GAME_NEXT_ROUND;
}

void PlayerAI::DrawCards(WINDOW *win, bool player, int size) const {
    box(win,0,0);
    mvwaddstr(win, 1, 2, "PRAVE HRAJE POCITAC");
}

void PlayerAI::DrawInfo(WINDOW *win, int max_col, int size) const {
    box(win,0,0);
    mvwaddstr(win, 1, 2, "PRAVE HRAJE POCITAC");
}



void PlayerAI::ThrowCard() {
    vector<int> types = {0, 0, 0, 0};
    for(auto n : cards_hand) {
        types[n->GetType()]++;
    }
    int i = 0;
    int throw_away = 0;
    int delete_card = 0;
    for(auto n : types) {
        if(n > throw_away) {
            throw_away = n;
            delete_card = i;
        }
        i++;
    }
    i = 0;
    int lowest_value = 0;
    for(auto n : cards_hand) {
        if(i == 0)
            lowest_value = n->GetValue();
        if(n->GetType() == delete_card && n->GetValue() <= lowest_value) {
            lowest_value = n->GetValue();
            cursor_position = i;
        }
        i++;
    }
}