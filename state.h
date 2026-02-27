#pragma once

#include <string>
#include "automate.h"
#include "symbole.h"
using namespace std;

class Automate;

class State {
    public:
        State(string name);
        virtual ~State() {};
        virtual bool transition(Automate & automate, Symbole * s) = 0;
        friend std::ostream& operator<<(std::ostream& out, const State& s);

    protected:
        string name;
};

class E0 : public State {
    public:
        E0() : State("E0") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E1 : public State {
    public:
        E1() : State("E1") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E2 : public State {
    public:
        E2() : State("E2") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E3 : public State {
    public:
        E3() : State("E3") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E4 : public State {
    public:
        E4() : State("E4") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E5 : public State {
    public:
        E5() : State("E5") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E6 : public State {
    public:
        E6() : State("E6") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E7 : public State {
    public:
        E7() : State("E7") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E8 : public State {
    public:
        E8() : State("E8") {}
        bool transition(Automate & automate, Symbole * s) override;
};

class E9 : public State {
    public:
        E9() : State("E9") {}
        bool transition(Automate & automate, Symbole * s) override;
};

