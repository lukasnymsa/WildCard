#include "HealCard.hpp"

bool HealCard::UseCard(Player &owner, Player &enemy) const {
    if(owner.Heal(value)) {
        owner.EraseCard(name);
        return true;
    }
    return false;
}
