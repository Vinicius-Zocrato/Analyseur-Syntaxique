#include <iostream>
#include <sstream>
#include <string>
#include "lexer.h"
#include "automate.h"
#include "state.h"

using namespace std;

static int passed = 0;
static int failed = 0;

static void check(const string& name, bool cond)
{
    cout << (cond ? "  [OK]  " : "  [FAIL]  ") << name << "\n";
    cond ? ++passed : ++failed;
}

// Retourne {valide, résultat} en supprimant la sortie de débogage
static pair<bool, int> parse(const string& expr)
{
    ostringstream devnull;
    streambuf* orig = cout.rdbuf(devnull.rdbuf());

    Lexer    l(expr);
    Automate a(&l);
    a.pushState(new E0);

    while (!a.isEnded() && !a.isError())
        a.getLastStateList()->transition(a, l.Consulter());

    cout.rdbuf(orig);
    return { a.isEnded() && !a.isError(), a.getResult() };
}

int main()
{
    // Expressions valides : {expression, résultat attendu}
    cout << "=== Expressions valides ===\n";
    pair<const char*, int> valides[] = {
        { "0",               0     },
        { "1",               1     },
        { "42",              42    },
        { "1000",            1000  },
        { "1+2",             3     },
        { "1+2+3",           6     },
        { "3*4",             12    },
        { "2*3*4",           24    },
        { "1+2*3",           7     },  // précédence : 1 + (2*3)
        { "2*3+4*5",         26    },  // précédence : (2*3) + (4*5)
        { "(1+2)",           3     },
        { "(1+2)*3",         9     },
        { "2*(3+4)",         14    },
        { "(1+2)*(3+4)",     21    },
        { "((2+3))",         5     },
        { "(1+36)*123*2",    9102  },
    };
    for (auto& [expr, attendu] : valides) {
        auto [valid, val] = parse(expr);
        check(string("\"") + expr + "\" == " + to_string(attendu), valid && val == attendu);
    }

    // Expressions invalides : {expression, raison}
    cout << "\n=== Expressions invalides ===\n";
    pair<const char*, const char*> invalides[] = {
        { "(1+2",  "parenthèse non fermée"       },
        { "1+2)",  "parenthèse inattendue"        },
        { "1++2",  "double opérateur +"           },
        { "1+*2",  "opérateurs consécutifs"       },
        { "1+",    "opérande manquante"           },
        { "*1",    "commence par *"               },
        { "+1",    "commence par +"               },
        { "()",    "parenthèses vides"            },
        { "1$2",   "caractère inconnu"            },
    };
    for (auto& [expr, raison] : invalides) {
        auto [valid, _] = parse(expr);
        check(string("\"") + expr + "\" invalide  [" + raison + "]", !valid);
    }

    cout << "\n===================================\n";
    cout << "Résultat: " << passed << " réussi(s), " << failed << " échoué(s)\n";
    cout << "===================================\n";
    return failed == 0 ? 0 : 1;
}
