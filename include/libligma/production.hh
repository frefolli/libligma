#ifndef LIBLIGMA_PRODUCTION_HH
#define LIBLIGMA_PRODUCTION_HH
#include <vector>
#include <ostream>
#include <libligma/index_t.hh>

class Production {
    private:
        index_t left;
        std::vector<index_t> right;
    public:
        Production(index_t left,
                   std::vector<index_t> right);
        index_t getLeft();
        std::vector<index_t>& getRight();
};

std::ostream& operator<<(std::ostream& out, Production& production);
#endif
