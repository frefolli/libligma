#ifndef LIBLIGMA_PRODUCTION_HH
#define LIBLIGMA_PRODUCTION_HH
#include <libligma/types.hh>

typedef struct {
    /* Production(leftSymbolIndex,
     *            rightSymbolsIndex)
     * */
    public:
        index_t left;
        std::vector<indet_t> right;
} production_t;
#endif
