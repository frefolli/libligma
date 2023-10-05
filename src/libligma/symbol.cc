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

std::ostream& operator<<(std::ostream& out, Symbol& symbol) {
    out << symbol.getName();
    return out;
}

index_t getStart(std::vector<Symbol>& symbols) {
    return symbols.at(symbols.size() - 3);
}

index_t getEOL(std::vector<Symbol>& symbols) {
    return symbols.at(symbols.size() - 2);
}

index_t getEpilon(std::vector<Symbol>& symbols) {
    return symbols.at(symbols.size() - 1);
}
