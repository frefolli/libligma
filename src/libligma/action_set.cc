#include <libligma/action_set.hh>

ActionSet::ActionSet() {}

void ActionSet::build() {
    set = {};
}

Action& ActionSet::operator[](std::pair<index_t, index_t> entry) {
    return set[entry];
}
