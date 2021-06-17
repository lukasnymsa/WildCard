#ifndef WILDCARD_ATTACKCARD_HPP
#define WILDCARD_ATTACKCARD_HPP
#include "Card.hpp"
#include "Player.hpp"
#include "DefensiveCard.hpp"

#include <utility>
#include <algorithm>

class Player;

/**
 * Attacking type of card
 */
class AttackCard : public Card {
public:
    /**
     * Creates new instance of Card
     * @param name name of card
     * @param value value of card
     * @param type type of card
     */
    AttackCard(string name, const int & value, const int &type)
    : Card(move(name), value, type) { }
    /**
     * Checks if enemy player has a defensive card
     * One value == One defensive card
     * If enemy doesnt have enough of defensive card the remaining value is used to decrease health of enemy
     * @param owner Player who used this card
     * @param enemy Player who is under attack
     * @return True if card can be used
     */
    bool UseCard(Player & owner, Player & enemy) const override;
};
#endif //WILDCARD_ATTACKCARD_HPP
