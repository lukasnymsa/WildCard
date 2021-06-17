#ifndef WILDCARD_GAMECONFIG_HPP
#define WILDCARD_GAMECONFIG_HPP
#include "Card.hpp"
#include "Player.hpp"
#include "AttackCard.hpp"
#include "DefensiveCard.hpp"
#include "HealCard.hpp"
#include "TakeCard.hpp"
#include "PlayerAI.hpp"
#include "Constants.hpp"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdio>

class Player;
class Card;
using namespace std;

/**
 * Represents configuration of the game
 * Reads config files, saved files and can create and save new file
 */
class GameConfig {
public:
    /**
     * Initializes all variables
     */
    GameConfig();
    /**
     * Opens, read and save to local variables the whole config file
     * @param path path to the chosen file
     * @return true if file could be read
     */
    bool ReadConfigFile(const string & path);
    /**
     * Opens, read and save to local variables the whole saved config file
     * @param path path to the chosen file
     * @return true if file could be read
     */
    bool ReadSavedFile(const string & path);
    /**
     * Creates new files based on date and time
     * @param save_players players to be saved
     * @param player current player
     * @param is_AI true if the second player is AI controlled
     * @return true if the file could be created and variables could be saved
     */
    bool SaveFile(vector<Player*> save_players, int player, bool is_AI);
    /**
     * Returns random card from all cards read from config
     * @return random card
     */
    Card* ReturnRandomCard() const;
    /**
     * Searches for card based on name
     * @param name name of the searches card
     * @return searched card
     */
    Card* SearchCard(const string & name) const;
    /**
     * Returns loaded players from file
     * @return players loaded from file
     */
    vector<Player*> CopyPlayers() const;
    /**
     * Returns max_health of players
     * @return max_health of players
     */
    int GetHealth() const;
    /**
     * Returns current_player
     * @return current_player
     */
    int GetCurrentPlayer() const;
    /**
     * Returns max_cards_hand of players
     * @return max_cards_hand of players
     */
    unsigned int GetMaxCards() const;
    /**
     * Returns true if the second player is AI controlled
     * @return true if the second player is AI controlled
     */
    bool GetAI() const;
    /**
     * Deletes instance of GameConfig
     */
    ~GameConfig();
private:
    int max_health;
    int max_cards_hand;
    int current_player;
    int health1;
    int health2;
    bool player_AI;
    vector<Card*> cards;
    vector<Player*> players;
    static string GetType(int type);
    /**
     * Deletes all players if read saved file failed
     * @param is_build True if players were created
     */
    void DeletePlayers(bool is_build);
    /**
     * Creates new card
     * @param name name of card
     * @param buffer_r buffer includes type and value
     * @return
     */
    bool CreateCard(const string & name, const string & buffer_r);
    /**
     * Adds card to player's hands
     * @param name name of card
     * @param buffer_r buffer of other cards to be added
     * @return True if all cards could be added
     */
    bool AddCardsToPlayer(const string & name, string & buffer_r);
};
#endif //WILDCARD_GAMECONFIG_HPP
