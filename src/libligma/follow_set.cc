#include <libligma/follow_set.hh>
#include <libutils/sets.hh>

FollowSet::FollowSet() {}

void FollowSet::build(std::vector<Symbol>& symbols,
                     std::vector<Production>& grammar,
                     FirstSet& firstSet) {
    for (index_t i = 0; i < symbols.size(); i++) {
        set[i] = {};
    }
    index_t start = getStart(symbols);
    index_t eol = getEOL(symbols);
    index_t epsilon = getEpsilon(symbols);
    set[start] = {eol};
    bool changed = true;
    while (changed) {
        changed = false;
        for (Production& p : grammar) {
            index_t A = p.getLeft();
            std::vector<index_t> Bs = p.getRight();
            for (auto it = Bs.begin(); it != Bs.end(); ++it) {
                index_t B = *it;
                if ((it + 1) != Bs.end()) {
                    index_t q = *(it + 1);
                    changed |= set_union(set[B],
                                         set_diff(firstSet[q],
                                                  {epsilon}));
                    if (set_in(firstSet[q], {epsilon})) {
                        changed |= set_union(set[B], set[A]);
                    }
                } else {
                    changed |= set_union(set[B], set[A]);
                }
            }
        }
    }
}

std::set<index_t>& FollowSet::operator[](index_t index) {
    return set[index];
}
