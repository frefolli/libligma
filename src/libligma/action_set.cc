#include <libligma/action_set.hh>
#include <iostream>

ActionSet::ActionSet() {}

void ActionSet::build() {
    set = {};
}

void ActionSet::print(std::vector<Symbol>& symbols) {
    for (auto it = set.begin(); it != set.end(); ++it) {
        ActionKind kind = it->second.getKind();
        index_t arg = it->second.getArg();
        std::cout << "ACTION["
            << it->first.first
            << ", \"" << symbols[it->first.second].getName()
            << "\"] = " << kind;
        if (kind != ActionKind::ACCEPT) {
            std::cout << " " << arg;
        }
        std::cout << std::endl;
    }
}

Action& ActionSet::operator[](std::pair<index_t, index_t> entry) {
    return set[entry];
}
