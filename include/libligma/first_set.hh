#ifndef LIBLIGMA_FIRST_HH
#define LIBLIGMA_FIRST_HH
#include <libligma/types.hh>
#include <libligma/grammar.hh>
#include <set>

class FirstSet {
    private:
        std::map<index_t, std::set<index_t>> FIRST;
    public:
        FirstSet();
        void build(std::vector<index_t>* terminals,
                   std::vector<index_t>* nonterminals,
                   grammar_t* grammar);
        std::set<index_t>& get(index_t);
        void print(symbols_t* symbols);
};
#endif
