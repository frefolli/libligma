#include <libligma/asset.hh>
#include <libutils/sets.hh>
#include <libutils/deques.hh>
#include <libutils/vectors.hh>
#include <iostream>

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

std::set<Item> Asset::buildGoto(std::set<Item>& set, index_t next) {
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
            auto nset = buildGoto(set, next);
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

void Asset::printFirstSet() {
    firstSet.print(symbols);
}

void Asset::printFollowSet() {
    followSet.print(symbols);
}

void Asset::printRecordSet() {
    recordSet.print(symbols);
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

void Asset::printItem(const Item& item) {
    index_t prod = item.getProd();
    index_t next = item.getNext();
    index_t left = grammar[prod].getLeft();
    std::vector<index_t> right = grammar[prod].getRight();
    index_t lookahead = item.getLook();
    std::cout << "- " << symbols[left].getName() << " ->";
    for (index_t i = 0; i < right.size(); i++) {
        if (i == next) {
            std::cout << " •";
        }
        std::cout << " " << symbols[right[i]].getName();
    }
    if (next == right.size()) {
        std::cout << " *";
    }
    std::cout << ", " << symbols[lookahead].getName() << std::endl;
}

void Asset::printItemSet(std::set<Item>& set) {
    if (set.size() == 0) {
        std::cout << "{}" << std::endl;
        return;
    }
    std::cout << "{" << std::endl;
    for (auto it = set.begin(); it != set.end(); ++it) {
        printItem(*it);
    }
    std::cout << "}" << std::endl;
}

void Asset::printCollection() {
    index_t i = 0;
    for (auto set : collection) {
        std::cout << "#" << i++ << " : ";
        printItemSet(set);
    }
}
