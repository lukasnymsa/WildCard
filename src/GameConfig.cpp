#include "GameConfig.hpp"
#define MAX_HEALTH "max_health"
#define MAX_CARDS "max_cards_hand"
#define ATTACK "attack"
#define DEFENSIVE "def"
#define HEAL "heal"
#define TAKE "take"
#define HEALTH_PLAYER1 "health1"
#define HEALTH_PLAYER2 "health2"
#define CURRENT_PLAYER "current_player"
#define PLAYER1 "player1"
#define PLAYER2 "player2"
#define AI "player_AI"

GameConfig::GameConfig() {
    max_health = 0;
    max_cards_hand = 0;
    health1 = 0;
    health2 = 0;
    current_player = 0;
    player_AI = false;
    srand(time(nullptr));
}

bool GameConfig::ReadConfigFile(const string & path) {
    ifstream file;
    file.open(path);
    if(!file)
        return false;
    string line;
    while(getline(file, line)) {
        line.erase(remove_if(line.begin(),line.end(),::isspace), line.end());
        if(line.empty())
            continue;
        auto position = line.find('=');
        if(position == string::npos){
            file.close();
            return false;
        }
        auto name = line.substr(0, position);
        auto buffer_r = line.substr(position + 1);
        if(name.empty()  || name.size() > 20) {
            file.close();
            return false;
        }
        if (name == MAX_HEALTH && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5)
            max_health = stoi(buffer_r);
        else if (name == MAX_CARDS && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5)
            max_cards_hand = stoi(buffer_r);
        else {
            if(SearchCard(name) != nullptr) {
                file.close();
                return false;
            }
            if(!CreateCard(name, buffer_r)) {
                file.close();
                return false;
            }
        }
    }
    file.close();
    return !(cards.empty() || max_health <= 0 || max_cards_hand <= 0);
}

bool GameConfig::ReadSavedFile(const string & path) {
    ifstream file;
    file.open(path);
    if(!file || file.fail())
        return false;
    string line;
    bool is_build = false;
    bool AI_decided = false;
    while(getline(file, line)) {
        line.erase(remove_if(line.begin(),line.end(),::isspace), line.end());
        if(line.empty())
            continue;
        auto position = line.find('=');
        auto name = line.substr(0, position);
        auto buffer_r = line.substr(position + 1);
        if(position == string::npos || name.empty() || name.size() > 20){
            DeletePlayers(is_build);
            file.close();
            return false;
        }
        if(!is_build && max_health != 0 && health1 != 0 && health2 != 0 && AI_decided) {
            if(health1 > max_health)
                health1 = max_health;
            if(health2 > max_health)
                health2 = max_health;
            players.push_back(new Player(max_health, health1));
            if(player_AI)
                players.push_back(new PlayerAI(max_health, health2));
            else
                players.push_back(new Player(max_health, health2));
            is_build = true;
        }
        if (name == MAX_HEALTH && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5)
            max_health = stoi(buffer_r);
        else if (name == MAX_CARDS && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5)
            max_cards_hand = stoi(buffer_r);
        else if(name == CURRENT_PLAYER && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5)
            current_player = stoi(buffer_r)-1;
        else if(name == HEALTH_PLAYER1 && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5)
            health1 = stoi(buffer_r);
        else if(name == HEALTH_PLAYER2 && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5)
            health2 = stoi(buffer_r);
        else if(name == AI && all_of(buffer_r.begin(), buffer_r.end(), ::isdigit) && buffer_r.size() < 5) {
            if(stoi(buffer_r) > 1 || stoi(buffer_r) < 0) {
                DeletePlayers(is_build);
                file.close();
                return false;
            }
            player_AI = stoi(buffer_r) == 1;
            AI_decided = true;
        }
        else if(name == PLAYER1 || name == PLAYER2) {
            if(buffer_r.empty())
                continue;
            if(!AddCardsToPlayer(name, buffer_r)) {
                DeletePlayers(is_build);
                file.close();
                return false;
            }
        }
        else {
            if(SearchCard(name) != nullptr) {
                DeletePlayers(is_build);
                file.close();
                return false;
            }
            if(!CreateCard(name, buffer_r)) {
                DeletePlayers(is_build);
                file.close();
                return false;
            }
        }
    }
    file.close();
    return !(cards.empty() || max_health <= 0 || max_cards_hand <= 0 || health1 <= 0|| health2 <= 0 || current_player > 1 || current_player < 0);
}

bool GameConfig::SaveFile(vector<Player*> save_players, int player, bool is_AI) {
    auto start = chrono::system_clock::now();
    auto end = chrono::system_clock::now();
    chrono::duration<double> sec = end-start;
    time_t current_time = chrono::system_clock::to_time_t(end);
    string time = ctime(&current_time);
    time.erase(remove_if(time.begin(),time.end(),::isspace), time.end());
    transform(time.begin(),time.end(),time.begin(), [](char c) {
        return c == ':' ? '-' : c;
    });
    time = "saves/" + time;
    remove(time.c_str());
    ofstream file(time);
    if(!file || file.fail()) {
        file.close();
        return false;
    }
    file << AI << '=' << is_AI << endl;
    file << MAX_HEALTH <<'=' << max_health << endl;
    file << MAX_CARDS << '=' << max_cards_hand << endl;
    file << HEALTH_PLAYER1 << '=' << save_players[0]->GetHealth() << endl;
    file << HEALTH_PLAYER2 << '=' << save_players[1]->GetHealth() << endl;
    file << CURRENT_PLAYER << '=' << player+1 << endl;
    for(auto n : cards) {
        if(n->GetType() == DEF_CARD)
            file << n->GetName() << '=' << GetType(n->GetType()) << endl;
        else
            file << n->GetName() << '=' << GetType(n->GetType()) << ',' << n->GetValue() << endl;
    }
    file << PLAYER1 << '=';
    size_t i = 0;
    size_t amount_cards = save_players[0]->GetCards().size();
    for(auto n : save_players[0]->GetCards()) {
        if(i >= amount_cards-1)
            file << n->GetName();
        else
            file << n->GetName() << ',';
        i++;
    }
    file << endl;
    file << PLAYER2 << '=';
    i = 0;
    amount_cards = save_players[1]->GetCards().size();
    for(auto n : save_players[1]->GetCards()) {
        if(i >= amount_cards-1)
            file << n->GetName();
        else
            file << n->GetName() << ',';
        i++;
    }
    file.close();
    return true;
}

Card * GameConfig::ReturnRandomCard() const {
    if(cards.empty())
        return nullptr;
    return cards[rand() % cards.size()];
}

bool GameConfig::AddCardsToPlayer(const string & name, string & buffer_r) {
    if(name.back() > '2' || name.back() < '1' || players.empty())
        return false;
    int player_set = name.back() - '0' - 1;
    unsigned long position;
    while((position = buffer_r.find(',')) != string::npos) {
        auto name_card = buffer_r.substr(0, position);
        Card * new_card = SearchCard(name_card);
        if(new_card == nullptr)
            return false;
        players[player_set]->AddCard(new_card);
        buffer_r = buffer_r.substr(position + 1);
    }
    if(!buffer_r.empty()) {
        Card *new_card = SearchCard(buffer_r);
        if (new_card == nullptr)
            return false;
        players[player_set]->AddCard(new_card);
    }
    return true;
}

Card * GameConfig::SearchCard(const string & name) const {
    for(auto n : cards) {
        if(n->GetName() == name)
            return n;
    }
    return nullptr;
}

bool GameConfig::CreateCard(const string & name, const string & buffer_r) {
    if(buffer_r == DEFENSIVE) {
        cards.push_back(new DefensiveCard(name, 0, 1));
        return true;
    }
    auto position = buffer_r.find(',');
    auto type = buffer_r.substr(0, position);
    auto value = buffer_r.substr(position + 1);
    if(!all_of(value.begin(), value.end(), ::isdigit) || type.empty() || value.empty() || value.size() > 4)
        return false;
    if(type == ATTACK)
        cards.push_back(new AttackCard(name, stoi(value), 0));
    else if(type == HEAL)
        cards.push_back(new HealCard(name, stoi(value), 2));
    else if(type == TAKE)
        cards.push_back(new TakeCard(name, stoi(value), 3));
    else
        return false;
    return true;
}

vector<Player *> GameConfig::CopyPlayers() const {
    return players;
}

int GameConfig::GetHealth() const {
    return max_health;
}

int GameConfig::GetCurrentPlayer() const {
    return current_player;
}

unsigned int GameConfig::GetMaxCards() const {
    return max_cards_hand;
}

bool GameConfig::GetAI() const {
    return player_AI;
}

GameConfig::~GameConfig() {
    for(auto & n : cards) {
        delete n;
    }
}

string GameConfig::GetType(int type) {
    switch(type) {
        case ATT_CARD :
            return ATTACK;
        case DEF_CARD :
            return DEFENSIVE;
        case HEAL_CARD:
            return HEAL;
        case TAKE_CARD:
            return TAKE;
        default:
            return "";
    }
}

void GameConfig::DeletePlayers(bool is_build) {
    if(is_build && !players.empty()) {
        for(auto n : players)
            delete n;
    }
}