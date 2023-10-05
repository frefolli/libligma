#ifndef LIBLIGMA_FIRST_SET_HH
#define LIBLIGMA_FIRST_SET_HH
#include <libligma/symbol.hh>
#include <libligma/grammar.hh>
#include <vector>
#include <set>
#include <map>
class FirstSet {
    std::map<index_t, std::set<index_t>> set;
    public:
        FirstSet();
        void build(std::vector<Symbol>& symbols,
                   std::vector<Production>& grammar);
        void print(std::vector<Symbol>& symbols);
};
#endif