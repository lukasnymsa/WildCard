#ifndef WILDCARD_HEALCARD_HPP
#define WILDCARD_HEALCARD_HPP
#include "Card.hpp"
#include "Player.hpp"

/**
 * Healing type of card
 */
class HealCard : public Card {
public:
    /**
     * Creates new instance of Card
     * @param name name of card
     * @param value value of card
     * @param type type of card
     */
    HealCard(string name, const int & value, const int &type)
    : Card(move(name), value, type) { }
    /**
     * Checks if owner can be healed
     * @param owner Player who used this card
     * @param enemy Player who is under attack
     * @return True if card can be used
     */
    bool UseCard(Player & owner, Player & enemy) const override;
};
#endif //WILDCARD_HEALCARD_HPP
