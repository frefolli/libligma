#include <libligma/goto_set.hh>
#include <iostream>

GotoSet::GotoSet() {}

void GotoSet::build() {
    set = {};
}

void GotoSet::print(std::vector<Symbol>& symbols) {
    for (auto it = set.begin(); it != set.end(); ++it) {
        std::cout << "GOTO[" << it->first.first << ", \"" << symbols[it->first.second].getName() << "\"] = " << it->second << std::endl;
    }
}

index_t& GotoSet::operator[](std::pair<index_t, index_t> entry) {
    return set[entry];
}
