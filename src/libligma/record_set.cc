#include <libligma/record_set.hh>
#include <libutils/maps.hh>
#include <sstream>

RecordSet::RecordSet() {}

void RecordSet::build() {
    set = {};
}

index_t& RecordSet::operator[](std::pair<index_t, index_t> entry) {
    return set[entry];
}

bool RecordSet::has(std::pair<index_t, index_t> entry) {
    return map_in(set, entry);
}
