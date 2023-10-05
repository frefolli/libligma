#ifndef LIBLIGMA_ASSET_HH
#define LIBLIGMA_ASSET_HH
#include <libligma/symbol.hh>
#include <libligma/production.hh>
#include <vector>
#include <libligma/first_set.hh>
#include <libligma/follow_set.hh>
class Asset {
    private:
        std::vector<Symbol> symbols;
        std::vector<Production> grammar;
        FirstSet firstSet;
        FollowSet followSet;
        index_t target;
    public:
        Asset(std::vector<Symbol> symbols,
              std::vector<Production> grammar,
              index_t target);

        void build();
        void printFirstSet();
        void printFollowSet();
};
#endif
