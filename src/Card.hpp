#ifndef WILDCARD_CARD_HPP
#define WILDCARD_CARD_HPP
#include <string>
#include <utility>
#include "Player.hpp"
#include "Constants.hpp"
class Player;
using namespace std;

/**
 * Class holds information of the name, type and value of a card
 */
class Card {
public:
    /**
     * Creates new instance of Card
     * @param name name of card
     * @param value value of card
     * @param type type of card
     */
    Card(string  name, const int & value, const int & type);
    /**
     * Returns name of card
     * @return name of card
     */
    string GetName() const;
    /**
     * Returns type of card
     * @return type of card
     */
    int GetType() const;
    /**
     * Returns value of card
     * @return value of card
     */
    int GetValue() const;
    /**
     * Virtual Card, every type of card has its own implemetion
     * Checks if card can be used
     * Deletes itself from cards in hands of player
     * Can change player's health or cards
     * @param owner Player who used this card
     * @param enemy Player who is under attack
     * @return True if card can be used
     */
    virtual bool UseCard(Player & owner, Player & enemy) const = 0;
    /**
     * Default destructor of card
     */
    virtual ~Card() = default;
    /**
     * Compares two cards
     * @param right The second card which is being compared
     * @return True if the Cards are identical
     */
    bool operator == (const Card & right) const;
    /**
     * Copies second card to the first one
     * @param right Card which is being copied to the first one
     * @return New card identical with the second one
     */
    Card & operator = (const Card & right);
protected:
    string name;
    int value;
    int type;
};

#endif //WILDCARD_CARD_HPP
