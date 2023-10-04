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
