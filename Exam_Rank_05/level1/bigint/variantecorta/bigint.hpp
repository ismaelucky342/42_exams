#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include <string>

class bigint {
    std::string s; 

    public: 
        bigint(unsigned long long n = 0); 
        bigint operator+(const bigint &o) const; 
        bigint operator<<(int n) const;
        bigint operator>>(int n) const;
        bigint operator<<(const bigint &o) const;
        bigint operator>> (const bigint &o) const;
        
        bigint operator+=(const bigint &o) { *this = *this + o; return *this; }
        bigint operator++() { *this = *this + 1; return *this;}
        bigint operator++(int) { bigint r(*this); *this = *this + 1; return r;}
        bigint operator<<=(const bigint &o) { *this = *this << o; return *this; }
        bigint operator>>=(const bigint &o) { *this = *this >> o; return *this; }


        bool operator<(const bigint &o) const { return s.size() < o.s.size() || (s.size() == o.s.size() && s < o.s); }
        bool operator<=(const bigint &o) const { return s.size() < o.s.size() || (s.size() == o.s.size() && s <= o.s); }
        bool operator>(const bigint &o) const { return s.size() > o.s.size() || (s.size() == o.s.size() && s > o.s); }
        bool operator>=(const bigint &o) const { return s.size() > o.s.size() || (s.size() == o.s.size() && s >= o.s); }
        bool operator==(const bigint &o) const { return s == o.s; }
        bool operator!=(const bigint &o) const { return s != o.s; }

        friend std::ostream &operator<<(std::ostream &o, const bigint &b) { return o << b.s; }

};
#endif