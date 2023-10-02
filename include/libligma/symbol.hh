#ifndef LIBLIGMA_SYMBOL_HH
#define LIBLIGMA_SYMBOL_HH
#include <string>

typedef struct {
    std::string name;
    bool isTerminal;
} symbol_t;
#endif
