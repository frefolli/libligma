#include <libligma/asset.hh>

Asset::Asset(std::vector<Symbol> symbols,
             std::vector<Production> grammar,
             index_t target) :
    symbols(symbols), grammar(grammar), target(target) {}

void Asset::build() {
    // Adds needed symbols
    symbols.push_back(Symbol("S", false));
    symbols.push_back(Symbol("$", true));
    symbols.push_back(Symbol("e", true));
    // Adds needed productions
    grammar.push_back(Production(getStart(symbols),
                                 {target, getEOL(symbols)}));
    // Builds inner sets
    firstSet.build(symbols, grammar);
    followSet.build(symbols, grammar);
}

void Asset::printFirstSet() {
    firstSet.print(symbols);
}

void Asset::printFollowSet() {
    followSet.print(symbols);
}
