#ifndef LIBLIGMA_FOLLOW_SET_HH
#define LIBLIGMA_FOLLOW_SET_HH
#include <libligma/symbol.hh>
#include <libligma/production.hh>
#include <libligma/first_set.hh>
#include <vector>
#include <set>
#include <map>
class FollowSet {
    std::map<index_t, std::set<index_t>> set;
    public:
        FollowSet();
        void build(std::vector<Symbol>& symbols,
                   std::vector<Production>& grammar,
                   FirstSet& firstSet);
        void print(std::vector<Symbol>& symbols);
        std::set<index_t>& operator[](index_t index);
};
#endif
