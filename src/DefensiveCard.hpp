#ifndef WILDCARD_DEFENSIVECARD_HPP
#define WILDCARD_DEFENSIVECARD_HPP
#include <string>
#include "Card.hpp"
#include "Player.hpp"

/**
 * Defensive type of card
 */
class DefensiveCard : public Card {
public:
    /**
     * Creates new instance of Card
     * @param name name of card
     * @param value value of card
     * @param type type of card
     */
    DefensiveCard(string name, const int & value, const int &type)
        : Card(move(name), value, type) {
    }
    /**
     * Defensive card cannot be used, it has no influence on opponent
     * Is only used when being under attack
     * @param owner Player who used this card
     * @param enemy Player who is under attack
     * @return Always false
     */
    bool UseCard(Player & owner, Player & enemy) const override {
        return false;
    }
};

#endif //WILDCARD_DEFENSIVECARD_HPP
