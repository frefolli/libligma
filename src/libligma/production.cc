#include <libligma/production.hh>
#include <libutils/vectors.hh>

Production::Production(index_t left,
           std::vector<index_t> right) :
    left(left), right(right) {}

index_t Production::getLeft() {
    return left;
}

std::vector<index_t>& Production::getRight() {
    return right;
}
