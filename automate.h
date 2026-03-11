#pragma once
#include "state.h"
#include "symbole.h"
#include "lexer.h"
#include <string>
using namespace std;

class State;

class Automate
{
    public:
        Automate(Lexer *lexer);
        ~Automate();
        friend std::ostream& operator<<(std::ostream& out, const Automate& a);
        
        void pushState(State * s);
        void popState();
        void pushSymbole(Symbole * s);
        Symbole* popSymbole();

        void applyReduction(Symbole * symbol, int n);
        void applyTransition(Symbole * symbol, State * state);
        void applyShift(Symbole * symbol, State * state);

        State* getLastStateList();
        Symbole* getLastSymboleList();

        void setError(bool err) { error = err; }
        bool isError() const { return error; }
        void setEnded(bool end) { ended = end; }
        bool isEnded() const { return ended; }
        void setResult(int res) { result = res; }
        int getResult() const { return result; }
        void setErrorMessage(const string& msg) { errorMessage = msg; }
        std::string getErrorMessage() const { return errorMessage; }

    protected:
        State ** StateList;
        int StateListSize;
        int StateListCapacity;

        Symbole ** SymboleList;
        int SymboleListSize;
        int SymboleListCapacity;

        int result;
        bool error;
        bool ended;
        string errorMessage;

        Lexer *lexer;


};
