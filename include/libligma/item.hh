#ifndef LIBLIGMA_ITEM_HH
#define LIBLIGMA_ITEM_HH
#include <libligma/index_t.hh>
#include <iostream>

class Item {
    private:
        index_t prod;
        index_t next;
        index_t look;
    public:
        Item(index_t prod,
             index_t next,
             index_t look);
        index_t getProd() const;
        index_t getNext() const;
        index_t getLook() const;
        bool operator<(const Item& other) const;
        bool operator==(const Item& other) const;
        bool operator>(const Item& other) const;
};

std::ostream& operator<<(std::ostream& out, const Item& item);
#endif
