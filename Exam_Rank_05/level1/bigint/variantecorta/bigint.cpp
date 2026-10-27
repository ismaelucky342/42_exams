#include "bigint.hpp"
#include <sstream>
#include <cstdlib>

static void normalize(std::string &v) {
    if (v.empty()) {
        v = "0";
        return;
    }
    while (v.size() > 1 && v[0] == '0')
        v.erase(v.begin());
}

bigint::bigint(unsigned long long n) { std::ostringstream o; o << n; s = o.str(); }

bigint bigint::operator+(const bigint &o) const {
    bigint r; r.s.clear();
    for (size_t i = 0, c = 0; i < s.size() || i < o.s.size() || c; i++) {
        size_t x = c + (i < s.size() ? s[s.size() - 1 - i] - '0' : 0)
                     + (i < o.s.size() ? o.s[o.s.size() - 1 - i] - '0' : 0);
        r.s.insert(r.s.begin(), char(x % 10 + '0'));
        c = x / 10;
    }
    normalize(r.s);
    return r;
}

bigint bigint::operator<<(int n) const {
    bigint r(*this);

    while (n-- > 0)
        r.s += '0';
    normalize(r.s);
    return r;
}

bigint bigint::operator>>(int n) const {
    bigint r(*this);

    while (n-- > 0 && !r.s.empty())
        r.s.erase(r.s.end() - 1);
    normalize(r.s);
    return r;
}

// sobrecarga para poder hacer x << y cuando y es bigint
bigint bigint::operator<<(const bigint &o) const {
    return *this << std::atoi(o.s.c_str());
}

bigint bigint::operator>>(const bigint &o) const {
    return *this >> std::atoi(o.s.c_str());
}