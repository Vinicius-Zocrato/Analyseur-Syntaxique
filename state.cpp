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
            cout<<"Expression valide"<<endl;
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
        case FIN:
            Symbole* popped = automate.popSymbole();
            automate.applyReduction(new Expr(popped->getValeur()), 1);
        default:
            cout<<"Erreur de syntaxe"<<endl;
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
            //depiler symboles et ajouter le resultat
            automate.applyReduction(s, 3);
        
            break;
        case MULT:
            automate.applyShift(s, new E5);
            break;
        case CLOSEPAR:
            //depiler symboles et ajouter le resultat
            automate.applyReduction(s, 3);
            break;
        case FIN:
            //depiler symboles et ajouter le resultat
            automate.applyReduction(s, 3);
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
            //depiler symboles et ajouter le resultat
            automate.applyReduction(s, 3);
            break;
        case MULT:
            //depiler symboles et ajouter le resultat
            automate.applyReduction(s, 3);
            break;
        case CLOSEPAR:
            //depiler symboles et ajouter le resultat
            automate.applyReduction(s, 3);
            break;
        case FIN:
            //depiler symboles et ajouter le resultat
            automate.applyReduction(s, 3);
            break;
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
            //depiler symboles, récuperer la valeur de E entre les parenthèses
            automate.applyReduction(new Expr(automate.popSymbole()->getValeur()), 3);
            break;
        case MULT:
            automate.applyReduction(s, 3);
            break;
        case CLOSEPAR:
            automate.applyReduction(s, 3);
            break;
        case FIN:
            automate.applyReduction(s, 3);
            break;
        default:
            cout<<"Erreur de syntaxe"<<endl;
            automate.setError(true);
            break;
    }
    return false;
}