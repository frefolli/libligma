#ifndef LIBLIGMA_ACTION_HH
#define LIBLIGMA_ACTION_HH
#include <libligma/index_t.hh>

enum ActionKind {
    ACCEPT, SHIFT, REDUCE
};

class Action {
    private:
        ActionKind kind;
        index_t arg;
    public:
        Action(ActionKind kind = ACCEPT,
               index_t arg = 0);

        static Action accept();
        static Action shift(index_t arg);
        static Action reduce(index_t arg);
        
        ActionKind getKind();
        index_t getArg();
};
#endif
