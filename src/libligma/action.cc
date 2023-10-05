#include <libligma/action.hh>

Action::Action(ActionKind kind,
               index_t arg) :
    kind(kind), arg(arg) {}

ActionKind Action::getKind() {
    return kind;
}

index_t Action::getArg() {
    return arg;
}

Action Action::accept() {
    return Action(ActionKind::ACCEPT);
}

Action Action::shift(index_t arg) {
    return Action(ActionKind::SHIFT, arg);
}

Action Action::reduce(index_t arg) {
    return Action(ActionKind::REDUCE, arg);
}
