#include "ability.h"

Ability::Ability(int id, char c, const string& name,bool used)
    : id(id), c(c), abilityName(name), used(used) {}

Ability::~Ability() {}


int Ability::getId() const {return id;}
bool Ability::if_used() const {return used;}
char Ability::getChar() const {return c;}
string Ability::getName() const {return abilityName;}


