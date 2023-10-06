#include <libligma/first_set.hh>
#include <libutils/sets.hh>

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
                i += 1;
            }

            if ((i == Bs.size()) &&
                (set_in(set[Bs.back()], epsilon))) {
                changed |= set_union(set[A], {epsilon});
            }
        }
    }
}

std::set<index_t>& FirstSet::operator[](index_t index) {
    return set[index];
}
