#include <libligma/item.hh>

Item::Item(index_t prod,
           index_t next,
           index_t look) :
    prod(prod), next(next), look(look) {}

index_t Item::getProd() const {
    return prod;
}

index_t Item::getNext() const {
    return next;
}

index_t Item::getLook() const {
    return look;
}

bool Item::operator<(const Item& other) const {
    if (prod == other.prod) {
        if (next == other.next) {
            return look < other.look;
        } else {
            return next < other.next;
        }
    } else {
        return prod < other.prod;
    }
}

bool Item::operator==(const Item& other) const {
    return ((prod == other.prod) &&
            (next == other.next) &&
            (look == other.look));
}

bool Item::operator>(const Item& other) const {
    return other < *this;
}

std::ostream& operator<<(std::ostream& out, const Item& item)  {
    out << "[" << item.getProd() << ", " << item.getNext() << ", " << item.getLook() << "]";
    return out;
}
