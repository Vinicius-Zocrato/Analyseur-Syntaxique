#include <iostream>
#include <sstream>
#include <string>
#include "lexer.h"
#include "automate.h"
#include "state.h"
#include <vector>

using namespace std;

static bool expect(bool cond, const string &msg) {
    if (!cond) {
        cerr << "  ❌ " << msg << "\n";
    }
    return cond;
}

// 1. Symbole/Entier affichage
bool test1()
{
    ostringstream buf;
    auto old = cout.rdbuf(buf.rdbuf());
    Entier e(42);
    e.Affiche();
    cout.rdbuf(old);
    string out = buf.str();
    return expect(out == "INT(42)", "Entier::Affiche produced '" + out + "' instead of 'INT(42)'");
}

// 2. Lexer produces expected token sequence
bool test2()
{
    string s = "(1+2)";
    Lexer l(s);
    vector <int> expecteds = {OPENPAR, INT, PLUS, INT, CLOSEPAR, FIN};
    size_t idx = 0;
    while(true) {
        Symbole *sym = l.Consulter();
        int code = *sym;
        if (idx >= expecteds.size()) break;
        if (!expect(code == expecteds[idx], "lexer token " + to_string(idx) + " wrong"))
            return false;
        if (code == FIN) break;
        l.Avancer();
        idx++;
    }
    return true;
}

// 3. Automate push state
bool test3()
{
    Automate a(nullptr);
    a.pushState(new E0);
    a.pushState(new E1);
    ostringstream buf;
    buf << a;
    string out = buf.str();
    return expect(out.find("State: E0") != string::npos && out.find("State: E1") != string::npos,
                  "Automate output should contain both E0 and E1");
}

// 4. Automate push/pop symbole and pop messages
bool test4()
{
    Automate a(nullptr);
    Entier* e = new Entier(5);
    a.pushSymbole(e);
    ostringstream buf;
    auto old = cout.rdbuf(buf.rdbuf());
    a.popSymbole();
    cout.rdbuf(old);
    string out = buf.str();
    return expect(out.find("Popping symbole") != string::npos,
                  "popSymbole should print a message");
}

// 5. Operator<< of State
bool test5()
{
    E3 s;
    ostringstream buf;
    buf << s;
    string out = buf.str();
    return expect(out.find("State: E3") != string::npos,
                  "State operator<< should indicate E3");
}

int main()
{
    bool all = true;
    all &= test1();
    all &= test2();
    all &= test3();
    all &= test4();
    all &= test5();

    cout << (all ? "All tests passed\n" : "Some tests failed\n");
    return all ? 0 : 1;
}