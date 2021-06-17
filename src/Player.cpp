#include "Player.hpp"
#define K_QUIT 'q'
#define K_SAVE 's'
#define K_SPACE ' '
#define K_THROW 't'
#define MOVE_CURSOR 4
#define ATTACK "UTOK"
#define DEFENSIVE "OBRANA"
#define HEAL "LECBA"
#define TAKE "KRADEZ"

Player::Player(int max_health, int health) {
    this->max_health = max_health;
    max_cards = 0;
    this->health = health;
    column = 2;
    enemy_cards = 0;
    side = 0;
    amount_cards = 0;
    cursor_position = 0;
    too_many_cards = false;
}

int Player::NextAction(int key_input) {
    too_many_cards = false;
    switch(key_input) {
        case K_QUIT :
            return GAME_QUIT;
        case K_SAVE :
            if(cards_hand.size() > max_cards) {
                too_many_cards = true;
                return MOVE_CURSOR;
            }
            return GAME_SAVE;
        case K_ENTER :
            return GAME_USE_CARD;
        case K_SPACE :
            if(cards_hand.size() > max_cards) {
                too_many_cards = true;
                return MOVE_CURSOR;
            }
            return GAME_NEXT_ROUND;
        case K_THROW :
            if(!cards_hand.empty())
                cards_hand.erase(cards_hand.begin() + cursor_position);
            ShiftCursor();
            return MOVE_CURSOR;
        case KEY_UP :
            if(cursor_position != 0 && cursor_position != side*MAX_LINES_TO_PRINT && cursor_position != MAX_LINES_TO_PRINT){
                cursor_position--;
            }
            return MOVE_CURSOR;
        case KEY_DOWN :
            if(cursor_position != (cards_hand.size() - 1) && cursor_position != side*MAX_LINES_TO_PRINT+(MAX_LINES_TO_PRINT-1) && cursor_position != (MAX_LINES_TO_PRINT-1) && !cards_hand.empty()) {
                cursor_position++;
            }
            return MOVE_CURSOR;
        case KEY_LEFT :
            if(side != 0) {
                side--;
                cursor_position = side * MAX_LINES_TO_PRINT;
            }
            return MOVE_CURSOR;
        case KEY_RIGHT :
            if((side * MAX_LINES_TO_PRINT + MAX_LINES_TO_PRINT) < amount_cards) {
                side++;
                cursor_position = side * MAX_LINES_TO_PRINT;
            }
            return MOVE_CURSOR;
        default:
            return MOVE_CURSOR;
    }
}

void Player::AddCard(Card * card) {
    cards_hand.push_back(card);
}

Card * Player::PickCard() const{
    if(!cards_hand.empty())
        return cards_hand[cursor_position];
    return nullptr;
}

Card * Player::ReturnRandomCard() const{
    if(!cards_hand.empty())
        return cards_hand[rand() % cards_hand.size()];
    return nullptr;
}

void Player::DrawCards(WINDOW * win, bool player, int size) const{
    ClearWindow(win, size);
    box(win,0,0);
    string text_player = "PRAVE HRAJE HRAC: ";
    if(player)
        text_player.push_back('2');
    else
        text_player.push_back('1');
    mvwaddstr(win, 1, column, text_player.c_str());
    int row = 3;
    for(size_t i = side*MAX_LINES_TO_PRINT; (i < cards_hand.size()) && (i < side*MAX_LINES_TO_PRINT+MAX_LINES_TO_PRINT); i++) {
        string format = cursor_position == i ? cards_hand[i]->GetName() + "  <=" : cards_hand[i]->GetName();
        mvwaddstr(win, row, column, format.c_str());
        row++;
    }
    if(!cards_hand.empty()) {
        string arrow_left;
        string arrow_right;
        if(side != 0)
            arrow_left = "< ";
        if(side != amount_cards/MAX_LINES_TO_PRINT && amount_cards > MAX_LINES_TO_PRINT)
            arrow_right = " >";
        string text_side = "KARTA: " + arrow_left + to_string(cursor_position + 1) + '/' + to_string(amount_cards) + arrow_right;
        mvwaddstr(win, 9, column, text_side.c_str());
    }
    string text_max_cards = "MAX POCET KARET V RUCE = " + to_string(max_cards);
    mvwaddstr(win,10,column,(text_max_cards).c_str());
    if(too_many_cards)
        mvwaddstr(win, 12, column, "PRILIS MNOHO KARET V RUCE");
    mvwaddstr(win,14,column,"t - zahodit kartu | q - konec hry | s - ulozit a ukoncit");
    mvwaddstr(win,15,column,"ENTER - pouzit kartu | SPACE - ukoncit kolo");
}

void Player::DrawInfo(WINDOW *win, int max_col, int size) const{
    ClearWindow(win, size);
    box(win,0,0);
    string text_header = "DETAIL KARTY";
    string text_type = "TYP KARTY: ";
    string text_value = "HODNOTA: ";
    mvwaddstr(win, 1, max_col / 4 - (text_header.size() / 2), text_header.c_str());
    mvwaddstr(win, 2, column, text_type.c_str());
    mvwaddstr(win, 3, column, text_value.c_str());
    if(!cards_hand.empty()) {
        mvwaddstr(win, 2, column + text_type.size(), GetType(cards_hand[cursor_position]->GetType()).c_str());
        if(cards_hand[cursor_position]->GetType() != 1)
            mvwaddstr(win, 3, column + text_value.size(), to_string(cards_hand[cursor_position]->GetValue()).c_str());
    }
}

void Player::ChangeHealth(int value) {
    health -= value;
}

vector<Card *> Player::GetCards() const{
    return cards_hand;
}

void Player::SetCursor() {
    cursor_position = 0;
}

void Player::EraseCard(const string & name) {
    int i = 0;
    for(auto n : cards_hand) {
        if(n->GetName() == name) {
            cards_hand.erase(cards_hand.begin() + i);
            break;
        }
        i++;
    }
}

int Player::GetHealth() const{
    return health;
}

unsigned int Player::GetCursor() const{
    return cursor_position;
}

void Player::ShiftCursor() {
    if(cursor_position != 0)
        cursor_position--;
}

bool Player::Heal(int amount) {
    int diff_health = max_health - health;
    if(diff_health > 0) {
        health += amount;
        if(health > max_health)
            health = max_health;
        return true;
    }
    return false;
}

void Player::SetMaxCards(unsigned int amount) {
    max_cards = amount;
}

void Player::SetAmountCards(int amount) {
    enemy_cards = amount;
}

void Player::SumCards() {
    amount_cards = cards_hand.size();
    side = cursor_position/5;
}

Player & Player::operator = (const Player &other) {
    if(this == &other)
        return *this;
    this->max_health = other.max_health;
    this->health = other.health;
    this->column = other.column;
    this->enemy_cards = other.enemy_cards;
    this->side = other.side;
    this->amount_cards = other.amount_cards;
    this->cursor_position = other.cursor_position;
    for(auto n : this->cards_hand) {
        delete n;
    }
    this->cards_hand = other.cards_hand;
    return *this;
}

void Player::ClearWindow(WINDOW *screen, int size) {
    wmove(screen, 1, 0);
    for(int i = 2; i <= size; i++) {
        wclrtoeol(screen);
        wmove(screen, i, 0);
    }
}

string Player::GetType(int type) {
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
