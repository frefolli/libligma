#ifndef LIBLIGMA_ACTION_SET_HH
#define LIBLIGMA_ACTION_SET_HH
#include <map>
#include <libligma/index_t.hh>
#include <libligma/action.hh>
#include <utility>
#include <set>

class ActionSet {
    std::map<std::pair<index_t, index_t>, Action> set;
    public:
        ActionSet();
        void build();
        Action& operator[](std::pair<index_t, index_t> entry);
};
#endif
