#ifndef LIBLIGMA_ITEM_HH
#define LIBLIGMA_ITEM_HH
#include <libligma/types.hh>

typedef struct {
    /* Item(productionIndex,
     *      nextSymbolIndex,
     *      lookAheadIndex)
     * */
    public:
        index_t prod;
        index_t next;
        index_t look;
} item_t;
#endif
