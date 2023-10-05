#include <libligma/follow_set.hh>

FollowSet::FollowSet() {}

void FollowSet::build(std::vector<Symbol>& symbols,
                     std::vector<Production>& grammar) {

}

void FollowSet::print(std::vector<Symbol>& symbols) {
    for (index_t i = 0; i < symbols.size(); i++) {
        std::cout << "FOLLOW[\"" << symbols[i].getName() << "\"] = {";
        for (auto sIt = set[i].begin(); sIt != set[i].end(); sIt++) {
            if (sIt != set[i].begin()) {
                std::cout << ", ";
            }
            std::cout << "\"" << symbols[*sIt].getName() << "\"";
        }
        std::cout << "}" << std::endl;
    }
}
