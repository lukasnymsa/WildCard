#include "TakeCard.hpp"

bool TakeCard::UseCard(Player &owner, Player &enemy) const {
    int amount_cards = 0;
    for(int i = 0; i < value; i++) {
        Card *taken_card = enemy.ReturnRandomCard();
        if (taken_card == nullptr) {
            break;
        }
        owner.AddCard(taken_card);
        enemy.EraseCard(taken_card->GetName());
        amount_cards++;
    }
    if(amount_cards != 0) {
        owner.EraseCard(name);
        return true;
    }
    return false;
}

