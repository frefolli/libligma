#ifndef LIBLIGMA_ACTION_SET_HH
#define LIBLIGMA_ACTION_SET_HH
#include <map>
#include <libligma/index_t.hh>
#include <libligma/symbol.hh>
#include <libligma/action.hh>
#include <utility>
#include <set>
#include <vector>

class ActionSet {
    std::map<std::pair<index_t, index_t>, Action> set;
    public:
        ActionSet();
        void build();
        void print(std::vector<Symbol>& symbols);
        Action& operator[](std::pair<index_t, index_t> entry);
};
#endif
