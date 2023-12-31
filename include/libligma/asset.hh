#ifndef LIBLIGMA_ASSET_HH
#define LIBLIGMA_ASSET_HH
#include <libligma/symbol.hh>
#include <libligma/production.hh>
#include <vector>
#include <libligma/first_set.hh>
#include <libligma/follow_set.hh>
#include <libligma/record_set.hh>
#include <libligma/action_set.hh>
#include <libligma/goto_set.hh>
#include <libligma/item.hh>
#include <set>

class Asset {
    private:
        std::vector<Symbol> symbols;
        std::vector<Production> grammar;
        FirstSet firstSet;
        FollowSet followSet;
        RecordSet recordSet;
        ActionSet actionSet;
        GotoSet gotoSet;
        std::vector<std::set<Item>> collection;
        index_t target;

        std::set<Item> buildSetZero();
        std::set<Item> buildClosure(std::set<Item>& set);
        std::vector<index_t> get_prods(index_t left);
        std::set<index_t> buildNexts(std::set<Item>& set);
        std::set<Item> buildNextItemSet(std::set<Item>& set, index_t next);
        void buildCollection();
        void buildActions();
    public:
        Asset(std::vector<Symbol> symbols,
              std::vector<Production> grammar,
              index_t target);

        void build();
};
#endif
