#include "automate.h"
#include "state.h"
#include <iostream>


Automate::Automate(Lexer *lexer) : StateListSize(0), StateListCapacity(10), SymboleListSize(0), SymboleListCapacity(10) {
    this->lexer = lexer;
    this->ended = false;
    this->error = false;
    this->result = 0;

    StateList = new State*[StateListCapacity];
    SymboleList = new Symbole*[SymboleListCapacity];
    for (int i = 0; i < StateListCapacity; i++) {
        StateList[i] = nullptr;
    }
    for (int i = 0; i < SymboleListCapacity; i++) {
        SymboleList[i] = nullptr;
    }
}

Automate::~Automate() {
    delete[] StateList;
    delete[] SymboleList;
}

std::ostream& operator<<(std::ostream& out, const Automate& a)
{
    out << "Automate: " << std::endl;
    out << "States: " << std::endl;
    for (int i = 0; i < a.StateListSize; i++) {
        out << *a.StateList[i] << std::endl;
    }
    out << "Symboles: " << std::endl;
    for (int i = 0; i < a.SymboleListSize; i++) {
        a.SymboleList[i]->Affiche();
        out << std::endl;
    }
    return out;
}

void Automate::pushState(State * s) {
    if (StateListSize == StateListCapacity) {
        StateListCapacity *= 2;
        State ** newStateList = new State*[StateListCapacity];
        for (int i = 0; i < StateListSize; i++) {
            newStateList[i] = StateList[i];
        }
        delete[] StateList;
        StateList = newStateList;
    }
    StateList[StateListSize++] = s;
}

void Automate::popState() {
    if (StateListSize > 0) {
        cout << "Popping state: " << *StateList[StateListSize - 1] << std::endl;
        StateListSize--;
    }
}

void Automate::pushSymbole(Symbole * s) {
    cout << "Pushing symbole: " << *s << std::endl;
    if (SymboleListSize == SymboleListCapacity) {
        SymboleListCapacity *= 2;
        Symbole ** newSymboleList = new Symbole*[SymboleListCapacity];
        for (int i = 0; i < SymboleListSize; i++) {
            newSymboleList[i] = SymboleList[i];
        }
        delete[] SymboleList;
        SymboleList = newSymboleList;
    }
    SymboleList[SymboleListSize++] = s;
}

Symbole* Automate::popSymbole() {
    if (SymboleListSize > 0) {
        Symbole* s = SymboleList[SymboleListSize - 1];
        cout << "Popping symbole: " << *s << std::endl;
        SymboleListSize--;
        return s;
    }
    return nullptr;
}

void Automate::applyReduction(Symbole * symbol, int n) {

    cout << "Applying reduction with symbol: " << *symbol << " and n: " << n << std::endl;
    cout << "Current state before reduction: " << *StateList[StateListSize - 1] << std::endl;
    
    for (int i = 0; i < n; i++) {
        popState();
    }

    this->getLastStateList()->transition(*this, symbol);
    
}

void Automate::applyTransition(Symbole * symbol, State * state) {
    pushSymbole(symbol);
    pushState(state);
}

void Automate::applyShift(Symbole * symbol, State * state) {
    pushSymbole(symbol);
    pushState(state);
    lexer->Avancer();
}

State* Automate::getLastStateList() {
    return StateList[StateListSize - 1];
}

Symbole* Automate::getLastSymboleList() {
    return SymboleList[SymboleListSize - 1];
}
