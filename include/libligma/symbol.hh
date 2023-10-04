#ifndef LIBLIGMA_SYMBOL_HH
#define LIBLIGMA_SYMBOL_HH
#include <string>
#include <ostream>

class Symbol {
    private:
        std::string name;
        bool terminality;
    public:
        Symbol(std::string name,
               bool terminality);
        std::string getName();
        bool isTerminal();
};

std::ostream& operator<<(std::ostream& out, Symbol& symbol);
#endif
