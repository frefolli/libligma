#ifndef LIBLIGMA_GOTO_SET_HH
#define LIBLIGMA_GOTO_SET_HH
#include <map>
#include <libligma/index_t.hh>
#include <utility>
#include <set>

class GotoSet {
    std::map<std::pair<index_t, index_t>, index_t> set;
    public:
        GotoSet();
        void build();
        index_t& operator[](std::pair<index_t, index_t> entry);
};
#endif
