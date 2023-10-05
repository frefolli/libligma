#include <libligma/record_set.hh>
#include <iostream>

RecordSet::RecordSet() {}

void RecordSet::build() {
    set = {};
}

void RecordSet::print(std::vector<Symbol>& symbols) {
    for (auto it = set.begin(); it != set.end(); ++it) {
        std::cout << "RECORD[" << it->first.first << ", \"" << symbols[it->first.second].getName() << "\"] = " << it->second << std::endl;
    }
}

index_t& RecordSet::operator[](std::pair<index_t, index_t> entry) {
    return set[entry];
}
