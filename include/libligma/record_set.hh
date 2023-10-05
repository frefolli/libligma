#ifndef LIBLIGMA_RECORD_SET_HH
#define LIBLIGMA_RECORD_SET_HH
#include <map>
#include <libligma/index_t.hh>
#include <libligma/symbol.hh>
#include <utility>
#include <set>
#include <vector>

class RecordSet {
    std::map<std::pair<index_t, index_t>, index_t> set;
    public:
        RecordSet();
        void build();
        void print(std::vector<Symbol>& symbols);
        index_t& operator[](std::pair<index_t, index_t> entry);
};
#endif
