#include <libligma/goto_set.hh>

GotoSet::GotoSet() {}

void GotoSet::build() {
    set = {};
}

index_t& GotoSet::operator[](std::pair<index_t, index_t> entry) {
    return set[entry];
}
