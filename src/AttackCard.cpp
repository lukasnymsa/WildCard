#include "AttackCard.hpp"

bool AttackCard::UseCard(Player &owner, Player &enemy) const {
    int amount = 0;
    for(auto n : enemy.GetCards()) {
        if(n->GetType() == DEF_CARD) {
            enemy.EraseCard(n->GetName());
            amount++;
        }
        if(amount == value)
            break;
    }
    if(amount != value)
        enemy.ChangeHealth(value - amount);
    owner.EraseCard(name);
    return true;
}

