#include <libligma/first_set.hh>
#include <libutils/sets.hh>
#include <iostream>

FirstSet::FirstSet() {}

void FirstSet::build(std::vector<Symbol>& symbols,
                     std::vector<Production>& grammar) {
    index_t epsilon = getEpsilon(symbols);
    for (index_t i = 0; i < symbols.size(); i++) {
        if (symbols[i].isTerminal())
            set[i] = {i};
        else
            set[i] = {};
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (Production& p : grammar) {
            index_t A = p.getLeft();
            std::vector<index_t> Bs = p.getRight();
            changed |= set_union(set[A],
                                 set_diff(set[Bs[0]],
                                          {epsilon}));
            index_t i = 0;
            while ((i < Bs.size() - 1) &&
                    set_in(set[Bs[i]], epsilon)) {
                changed |= set_union(set[A],
                                     set_diff(set[Bs[i+1]],
                                              {epsilon}));
            }

            if ((i == Bs.size()) &&
                (set_in(set[Bs.back()], epsilon))) {
                changed |= set_union(set[A], {epsilon});
            }
        }
    }
}

void FirstSet::print(std::vector<Symbol>& symbols) {
    for (index_t i = 0; i < symbols.size(); i++) {
        std::cout << "FIRST[\"" << symbols[i].getName() << "\"] = {";
        for (auto sIt = set[i].begin(); sIt != set[i].end(); sIt++) {
            if (sIt != set[i].begin()) {
                std::cout << ", ";
            }
            std::cout << "\"" << symbols[*sIt].getName() << "\"";
        }
        std::cout << "}" << std::endl;
    }
}
