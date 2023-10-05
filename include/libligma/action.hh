#ifndef LIBLIGMA_ACTION_HH
#define LIBLIGMA_ACTION_HH
#include <libligma/index_t.hh>
#include <ostream>

enum ActionKind {
    ACCEPT, SHIFT, REDUCE
};

class Action {
    private:
        ActionKind kind;
        index_t arg;
    public:
        Action(ActionKind kind,
               index_t arg);
        Action(ActionKind kind);

        static Action accept();
        static Action shift(index_t arg);
        static Action reduce(index_t arg);
        
        ActionKind getKind();
        index_t getArg();
};

std::ostream& operator<<(std::ostream& out, ActionKind kind);
#endif
