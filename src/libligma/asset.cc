#include <libligma/asset.hh>
#include <libutils/sets.hh>
#include <libutils/deques.hh>
#include <libutils/vectors.hh>

Asset::Asset(std::vector<Symbol> symbols,
             std::vector<Production> grammar,
             index_t target) :
    symbols(symbols), grammar(grammar), target(target) {}

void Asset::build() {
    // Adds needed symbols
    symbols.push_back(Symbol("S", false));
    symbols.push_back(Symbol("$", true));
    symbols.push_back(Symbol("e", true));
    // Adds needed productions
    grammar.push_back(Production(getStart(symbols),
                                 {target, getEOL(symbols)}));
    // Builds inner sets
    firstSet.build(symbols, grammar);
    followSet.build(symbols, grammar, firstSet);

    // Build collection (set zero + closures)
    buildCollection();

    // Build ACTION and GOTO sets
    buildActions();
}

void Asset::buildActions() {
    auto eol = getEOL(symbols);
    actionSet.build();
    gotoSet.build();

    for (index_t x = 0; x < collection.size(); x++) {
        auto set = collection[x];
        for (const Item item : set) {
            auto prod = item.getProd();
            auto next = item.getNext();
            auto look = item.getLook();
            auto rhs = grammar[prod].getRight();
            if ((prod == grammar.size()-1) &&
                    (next == rhs.size()) &&
                    (look == eol)) {
                actionSet[std::make_pair(x, eol)] = Action::accept();
            } else if ((next < rhs.size()) &&
                        (symbols[next].isTerminal()) &&
                        recordSet.has(std::make_pair(x, rhs[next]))) {
                actionSet[std::make_pair(x, rhs[next])] = Action::shift(recordSet[std::make_pair(x, rhs[next])]);
            } else if (next == rhs.size()) {
                actionSet[std::make_pair(x, look)] = Action::reduce(prod);
            }
        }
        for (index_t n = 0; n < symbols.size(); n++) {
            if (!(symbols[n].isTerminal()) &&
                  recordSet.has(std::make_pair(x, n))) {
                gotoSet[std::make_pair(x, n)] = recordSet[std::make_pair(x, n)];
            }
        }
    }
}

std::set<index_t> Asset::buildNexts(std::set<Item>& set) {
    std::set<index_t> nexts = {};
    for (auto item : set) {
        auto prod = grammar[item.getProd()];
        auto next = item.getNext();
        if (next < prod.getRight().size()) {
            set_join(nexts, prod.getRight()[next]);
        }
    }
    return nexts;
}

std::set<Item> Asset::buildNextItemSet(std::set<Item>& set, index_t next) {
    std::set<Item> result = {};
    for (auto item : set) {
        auto prod = grammar[item.getProd()];
        auto next_ = item.getNext();
        auto look = item.getLook();
        if (next_ < prod.getRight().size() && prod.getRight()[next_] == next) {
            auto nitem = Item(item.getProd(), next_+1, look);
            set_join(result, nitem);
        }
    }
    return buildClosure(result);
}

std::set<Item> Asset::buildSetZero() {
    std::set<Item> set_zero = {Item(grammar.size() - 1, 0, getEOL(symbols))};
    return buildClosure(set_zero);
}

void Asset::buildCollection() {
    collection = {};
    std::deque<std::set<Item>> deque = {buildSetZero()};
    while (deque.size() > 0) {
        auto set = deque.front();
        deque.pop_front();
        index_t j = collection.size();
        collection.push_back(set);
        index_t k = j + 1;
        for (auto next : buildNexts(set)) {
            auto nset = buildNextItemSet(set, next);
            index_t i = vector_index(collection, nset);
            if (i == k) {
                i = deque_index(deque, nset);
                if (i == deque.size()) {
                    deque.push_back(nset);
                }
                i += k;
            }
            recordSet[std::make_pair(j, next)] = i;
        }
    }
}

std::set<Item> Asset::buildClosure(std::set<Item>& set) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto it = set.begin(); it != set.end(); ++it) {
            auto item = *it;
            index_t prod = item.getProd();
            index_t next = item.getNext();
            if (next < grammar[prod].getRight().size()) {
                index_t sym = grammar[prod].getRight()[next];
                for (index_t p : get_prods(sym)) {
                    for (index_t b : followSet[sym]) {
                        auto nitem = Item(p, 0, b);
                        changed |= set_join(set, nitem);
                    }
                }
            }
            if (changed)
                break;
        }
    }
    return set;
}

std::vector<index_t> Asset::get_prods(index_t left) {
    std::vector<index_t> result = {};
    for (index_t i = 0; i < grammar.size(); i++) {
        if (grammar[i].getLeft() == left) {
            result.push_back(i);
        }
    }
    return result;
}
