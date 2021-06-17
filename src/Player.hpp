#ifndef WILDCARD_PLAYER_HPP
#define WILDCARD_PLAYER_HPP
#include "Card.hpp"
#include "curses.h"
#include "Constants.hpp"
#include <vector>
#include <string>
class Card;
using namespace std;

/**
 * Represents single player
 * His cards, health, cursor_position etc.
 */
class Player {
public:
    /**
     * Creates a new player
     * @param max_health maximal health of the player
     * @param health starting health of the player
     */
    Player(int max_health, int health);
    /**
     * Changes side and cursor position
     * Decides what will happen based on pressed key
     * @param key_input current pressed key
     * @return returns reaction to GameScreen based on chosen key
     */
    virtual int NextAction(int key_input);
    /**
     * Adds card to the player's hands
     * @param card card to be added to the hands of player
     */
    void AddCard(Card * card);
    /**
     * Returns selected card
     * @return selected card
     */
    Card* PickCard() const;
    /**
     * Returns random card from player's hands
     * @return random card from player's hands
     */
    Card* ReturnRandomCard() const;
    /**
     * Draws all Cards in players' hands
     * Draws needed info for current player
     * @param win window to draw in
     * @param player current player
     * @param size rows of current screen
     */
    virtual void DrawCards(WINDOW * win, bool player, int size) const;
    /**
     * Draws info to selected card and other needed info
     * @param win window to draw in
     * @param max_col amount of collumns of the screen
     * @param size rows of current screen
     */
    virtual void DrawInfo(WINDOW * win, int max_col, int size) const;
    /**
     * Deducts health
     * @param value value which will be subtracted from player's health
     */
    void ChangeHealth(int value);
    /**
     * Returns vector of cards in player's hands
     * @return all cards in player's hands
     */
    vector<Card*> GetCards() const;
    /**
     * sets cursor_position to 0
     */
    void SetCursor();
    /**
     * Search for cards in hands of player
     * Compares name
     * @param name name of the searched card
     */
    void EraseCard(const string& name);
    /**
     * Returns player's current health
     * @return player's current health
     */
    int GetHealth() const;
    /**
     * Returns cursor_position
     * @return cursor_position
     */
    unsigned int GetCursor() const;
    /**
     *  Reduces the cursor_position value by 1
     */
    void ShiftCursor();
    /**
     * Adds value to the player's health
     * @param amount by how much the health will increase
     * @return true if player could be healed
     */
    bool Heal(int amount);
    /**
     * Sets max_cards by amount
     * @param amount amount of max_cards
     */
    void SetMaxCards(unsigned int amount);
    /**
     * Sets amount of enemy_cards
     * @param amount amount of enemy cards
     */
    void SetAmountCards(int amount);
    /**
     * Sets amount_cards to the current size of cards_hand
     * Sets side to the current cursor_position divided by 5
     */
    void SumCards();
    /**
     * Deletes instance of Player
     */
    virtual ~Player() = default;
    /**
     * Copies second player to the first one
     * @param other second player being copied
     * @return copied player
     */
    Player & operator = (const Player & other);
protected:
    int max_health;
    unsigned int max_cards;
    int health;
    int column;
    int enemy_cards;
    bool too_many_cards;
    unsigned int side;
    unsigned int amount_cards;
    unsigned int cursor_position;
    vector<Card*> cards_hand;
    static void ClearWindow(WINDOW * screen, int size);
    static string GetType(int type);
};
#endif //WILDCARD_PLAYER_HPP
