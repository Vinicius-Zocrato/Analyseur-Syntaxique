#include <iostream>
#include "lexer.h"
#include "automate.h"
#include "state.h"

int main(void) {
   string chaine("(1+36)*123*2");

   Lexer l(chaine);

   Symbole * s;

   l.Reset();

   Automate a(&l);
   a.pushState(new E0);

   while (!a.isEnded() && !a.isError()) {
      s = l.Consulter();
      a.getLastStateList()->transition(a, s);
   }
   
   cout << endl;
   cout << "===============================" << endl;
   cout << "Expression : " << chaine << endl;
   cout << "===============================" << endl;
   if (a.isEnded() && !a.isError()) {
      cout << "Expression valide" << endl;
      cout << "Resultat: " << a.getResult() << endl;
   }
   else {
      cout << "Expression invalide" << endl;
      cout << "Erreur : " << a.getErrorMessage() << endl;
   }

   return 0;
}

