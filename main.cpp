#include <iostream>
#include "lexer.h"
#include "automate.h"
#include "state.h"

int main(void) {
   string chaine("(1+36)*123*2");

   Lexer l(chaine);

   Symbole * s;
   // while(*(s=l.Consulter())!=FIN) {
   //    s->Affiche();
   //    cout<<endl;
   //    l.Avancer();
   // }

   l.Reset();

   Automate a(&l);
   a.pushState(new E0);
   

   while (!a.isEnded() && !a.isError()) {
      s = l.Consulter();
      a.getLastStateList()->transition(a, s);
     //comprendre le problème avec ça: si on fait un décalage et transition
     // on fait toujours appel à transition avec le même symbole
     //il faut consulter quelque part pour un nouveau symbole je crois
   }
   
   if (a.isEnded() && !a.isError()) {
      cout << "Expression valide" << endl;
      cout << "Resultat: " << a.getResult() << endl;
   }
   else {
      cout << "Expression invalide" << endl;
   }

   return 0;
}

