#include <libligma/symbol.hh>

Symbol::Symbol(std::string name,
       bool terminality) :
    name(name), terminality(terminality) {}

std::string Symbol::getName() {
    return name;
}

bool Symbol::isTerminal() {
    return terminality;
}

index_t getStart(std::vector<Symbol>& symbols) {
    return (symbols.size() - 3);
}

index_t getEOL(std::vector<Symbol>& symbols) {
    return (symbols.size() - 2);
}

index_t getEpsilon(std::vector<Symbol>& symbols) {
    return (symbols.size() - 1);
}
