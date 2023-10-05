#include <libligma/action.hh>

Action::Action(ActionKind kind,
               index_t arg) :
    kind(kind), arg(arg) {}

Action::Action(ActionKind kind) :
    kind(kind) {}

ActionKind Action::getKind() {
    return kind;
}

index_t Action::getArg() {
    return arg;
}

std::ostream& operator<<(std::ostream& out, ActionKind kind) {
    switch (kind) {
        case ActionKind::ACCEPT : out << "Accept"; break;
        case ActionKind::SHIFT  : out << "Shift"; break;
        case ActionKind::REDUCE : out << "Reduce"; break;
    }
    return out;
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
