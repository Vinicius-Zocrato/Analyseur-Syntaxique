#include "state.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const State& s)
{
    out << "State: " << s.name;
    return out;
}

State::State(string name) : name(name) {}

bool E0::transition(Automate & automate, Symbole * s){
    switch(*s){
        case INT:
            automate.applyShift(s, new E3);
            break;
        case OPENPAR:
            automate.applyShift(s, new E2);
            break;
        case EXPR:
            automate.applyTransition(s, new E1);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E1::transition(Automate & automate, Symbole * s){
    switch(*s){
        case PLUS:
            automate.applyShift(s, new E4);
            break;
        case MULT:
            automate.applyShift(s, new E5);
            break;
        case FIN:
            automate.setResult(static_cast<Expr*>(automate.getLastSymboleList())->getValeur());
            automate.setEnded(true);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E2::transition(Automate & automate, Symbole * s){
    switch(*s){
        case INT:
            automate.applyShift(s, new E3);
            break;
        case OPENPAR:
            automate.applyShift(s, new E2);
            break;
        case EXPR:
            automate.applyTransition(s, new E6);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E3::transition(Automate & automate, Symbole * s){
    switch(*s){
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN: {
            Symbole* popped = automate.popSymbole();
            int valeur = static_cast<Expr*>(popped)->getValeur();
            automate.applyReduction(new Expr(valeur), 1);
            break;
        }
        default:
            cout << "Erreur de syntaxe" << endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E4::transition(Automate & automate, Symbole * s){
    switch(*s){
        case INT:
            automate.applyShift(s, new E3);
            break;
        case OPENPAR:
            automate.applyShift(s, new E2);
            break;
        case EXPR:
            automate.applyTransition(s, new E7);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E5::transition(Automate & automate, Symbole * s){
    switch(*s){
        case INT:
            automate.applyShift(s, new E3);
            break;
        case OPENPAR:
            automate.applyShift(s, new E2);
            break;
        case EXPR:
            automate.applyTransition(s, new E8);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E6::transition(Automate & automate, Symbole * s){
    switch(*s){
        case PLUS:
            automate.applyShift(s, new E4);
            break;
        case MULT:
            automate.applyShift(s, new E5);
            break;
        case CLOSEPAR:
            automate.applyShift(s, new E9);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E7::transition(Automate & automate, Symbole * s){
    switch(*s){
        case PLUS:
        case CLOSEPAR:
        case FIN: {
            Symbole* popped1 = automate.popSymbole();
            automate.popSymbole(); //pop the PLUS symbol
            Symbole* popped2 = automate.popSymbole();
            int valeur1 = static_cast<Expr*>(popped1)->getValeur();
            int valeur2 = static_cast<Expr*>(popped2)->getValeur();
            automate.applyReduction(new Expr(valeur1 + valeur2), 3);
            break;
        }
        case MULT:
            automate.applyShift(s, new E5);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E8::transition(Automate & automate, Symbole * s){
    switch(*s){
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN: {
            Symbole* popped1 = automate.popSymbole();
            automate.popSymbole(); //pop the MULT symbol
            Symbole* popped2 = automate.popSymbole();
            int valeur1 = static_cast<Expr*>(popped1)->getValeur();
            int valeur2 = static_cast<Expr*>(popped2)->getValeur();
            automate.applyReduction(new Expr(valeur1 * valeur2), 3);
            break;
        }
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}

bool E9::transition(Automate & automate, Symbole * s){
    switch(*s){
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN: {
            automate.popSymbole(); //pop the OPENPAR symbol
            Symbole* popped1 = automate.popSymbole();
            automate.popSymbole(); //pop the CLOSEPAR symbol
            int valeur1 = static_cast<Expr*>(popped1)->getValeur();
            automate.applyReduction(new Expr(valeur1), 3);
            break;
        }
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}