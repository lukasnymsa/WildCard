#ifndef WILDCARD_PLAYERAI_HPP
#define WILDCARD_PLAYERAI_HPP
#include "Player.hpp"


/**
 * Represents AI player
 * Its cards, health, cursor_position etc.
 */
class PlayerAI : public Player {
public:
    /**
     * Creates a new AI player
     * @param max_health maximal health of the player
     * @param health starting health of the player
     */
    explicit PlayerAI(int max_health, int health) : Player(max_health, health) {}
    /**
     * AI decides what card to pick and use
     * @param key_input no implemtation in AI player
     * @return reaction to GameScreen based on chosen key
     */
    int NextAction(int key_input) override;
    /**
     * Draws only text so player cant see AI's cards and info
     * @param win window to draw in
     * @param player current player
     * @param size rows of current screen
     */
    void DrawCards(WINDOW * win, bool player, int size) const override;
    /**
     * Draws only text so player cant see AI's cards and info
     * @param win window to draw in
     * @param max_col amount of collumns of the screen
     * @param size rows of current screen
     */
    void DrawInfo(WINDOW * win, int max_col, int size) const override;
    /**
     * Deletes instance of PlayerAI
     */
    ~PlayerAI() override = default;
private:
    void ThrowCard();
};

#endif //WILDCARD_PLAYERAI_HPP
