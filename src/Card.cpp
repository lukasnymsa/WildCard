#include "Card.hpp"

Card::Card(string name, const int &value, const int &type)
        :   name(move(name)),
            value(value),
            type(type)
{}

string Card::GetName() const {
    return name;
}

int Card::GetType() const {
    return type;
}

int Card::GetValue() const {
    return value;
}

bool Card::operator==(const Card &right) const {
    return this->type == right.type;
}

Card & Card::operator=(const Card &right) {
    if(this == &right)
        return *this;
    this->name = right.name;
    this->value = right.value;
    this->type = right.type;
    return *this;
}

