#ifndef LIBLIGMA_SYMBOL_HH
#define LIBLIGMA_SYMBOL_HH
#include <string>
#include <ostream>
#include <vector>
#include <libligma/index_t.hh>

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
index_t getStart(std::vector<Symbol>& symbols);
index_t getEOL(std::vector<Symbol>& symbols);
index_t getEpilon(std::vector<Symbol>& symbols);
#endif
