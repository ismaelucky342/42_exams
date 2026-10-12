#include "bigint.hpp"
#include <sstream>
#include <cstdlib>

bigint::bigint(unsigned long long n) { std::ostringstream o; o << n; s = o.str(); }

bigint bigint::operator+(const bigint &o) const {
    bigint r; r.s.clear();
    for (size_t i = 0, c = 0; i < s.size() || i < o.s.size() || c; i++) {
        size_t x = c + (i < s.size() ? s[s.size() - 1 - i] - '0' : 0)
                     + (i < o.s.size() ? o.s[o.s.size() - 1 - i] - '0' : 0);
        r.s.insert(r.s.begin(), char(x % 10 + '0'));
        c = x / 10;
    }
    return r;
}

bigint bigint::operator<<(const bigint &o) const {
    bigint r(*this);
    if (s != "0") r.s += std::string(atoi(o.s.c_str()), '0');
    return r;
}

bigint bigint::operator>>(const bigint &o) const {
    size_t n = atoi(o.s.c_str());
    bigint r(*this);
    r.s = n >= s.size() ? "0" : s.substr(0, s.size() - n);
    return r;
}