#include <libligma/asset.hh>
#include <iostream>

Asset::Asset(symbols_t symbols,
              std::vector<index_t> terminals,
              std::vector<index_t> nonterminals,
              grammar_t grammar) : symbols(symbols),
                                   terminals(terminals),
                                   nonterminals(nonterminals),
                                   grammar(grammar) {
    first_set.build(&(this->terminals),
                    &(this->nonterminal),
                    &(this->grammar));
}

void Asset::print_first_set() {
    first_set.print(&(this->symbols));
}
void Asset::print_grammar() {
    std::ostringstream out ("");
    for (auto it = grammar.begin(); it != grammar.end(); it++) {
        out.str(symbols[it->left].name);
        out << " -->";
        if (rhs.size() > 0) {
            for (auto sym = rhs.begin(); sym != ths.end(); sym++) {
                out << " " << symbols[it->left].name;
            }
        }
        std::cout << out.str() << std::endl;
    }
}
