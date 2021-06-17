#ifndef WILDCARD_TAKECARD_HPP
#define WILDCARD_TAKECARD_HPP
#include "Card.hpp"
#include "Player.hpp"

/**
 * Taking type of card
 */
class TakeCard : public Card {
public:
    /**
     * Creates new instance of Card
     * @param name name of card
     * @param value value of card
     * @param type type of card
     */
    TakeCard(string name, const int & value, const int &type)
    : Card(move(name), value, type) {
    }
    /**
     * Checks if enemy has enough cards to be taken
     * Then adds them in to owner's hands
     * @param owner Player who used this card
     * @param enemy Player who is under attack
     * @return True if card can be used
     */
    bool UseCard(Player & owner, Player & enemy) const override;
};
#endif //WILDCARD_TAKECARD_HPP
