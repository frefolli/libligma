#ifndef LIBLIGMA_ASSET_HH
#define LIBLIGMA_ASSET_HH
#include <libligma/symbol.hh>
#include <libligma/grammar.hh>
#include <vector>
class Asset {
    private:
        std::vector<Symbol> symbols;
        std::vector<Production> grammar;
    public:
        Asset(std::vector<Symbol> symbols,
                std::vector<Production> grammar);
};
#endif
