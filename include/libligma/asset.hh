#ifndef LIBLIGMA_ASSET_HH
#define LIBLIGMA_ASSET_HH
#include <libligma/grammar.hh>
#include <libligma/symbols.hh>
#include <libligma/first_set.hh>

class Asset {
    /* Assumes:
     * - symbols contains "" and $
     * - grammar contains [S' -> S $]
     * */
    private:
        FirstSet first_set;
        symbols_t symbols,
        std::vector<index_t> terminals,
        std::vector<index_t> nonterminals,
        grammar_t grammar
    public:
        Asset(symbols_t symbols,
              std::vector<index_t> terminals,
              std::vector<index_t> nonterminals,
              grammar_t grammar);

        void print_first_set();
        void print_grammar();
};
#endif
