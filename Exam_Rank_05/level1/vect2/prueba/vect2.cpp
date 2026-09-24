#include "vect2.hpp"

vect2::vect2(int x, int y) {
    v[0] = x;
    v[1] = y;
}

int& vect2::operator[](int index) {
    return v[index];
}

const int& vect2::operator[](int index) const {
    return v[index];
}

std::ostream& operator<<(std::ostream &os, const vect2& other)
{
    os << "{" << other[0] << ", " << other[1] << "}";
    return os;
}

vect2 vect2::operator+(const vect2 &other) const
{
    return vect2((*this)[0] + other[0], (*this)[1] + other[1]);
}

vect2 vect2::operator-(const vect2 &other) const
{
    return vect2((*this)[0] - other[0], (*this)[1] - other[1]);
}

vect2 vect2::operator*(int scalar) const
{
    return vect2((*this)[0] * scalar, (*this)[1] * scalar);
}

vect2 vect2::operator/(int scalar) const
{
    return vect2((*this)[0] / scalar, (*this)[1] / scalar);
}

vect2& vect2::operator*=(int scalar)
{
    (*this)[0] *= scalar;
    (*this)[1] *= scalar;
    return *this;
}

vect2& vect2::operator/=(int scalar)
{
    (*this)[0] /= scalar;
    (*this)[1] /= scalar;
    return *this;
}

vect2& vect2::operator+=(const vect2& other)
{
    (*this)[0] += other[0];
    (*this)[1] += other[1];
    return *this;
}
vect2& vect2::operator-=(const vect2& other){
    (*this)[0] -= other[0];
    (*this)[1] -= other[1];
    return *this;
}

vect2& vect2::operator++()
{
    (*this)[0]++;
    (*this)[1]++;
    return *this;
}

vect2& vect2::operator--()
{
    (*this)[0]--;
    (*this)[1]--;
    return *this;
}

vect2  vect2::operator++(int)
{
    vect2 temp(*this);
    (*this)[0]++;
    (*this)[1]++;
    return temp;
}

vect2  vect2::operator--(int)
{
    vect2 temp(*this);
    (*this)[0]--;
    (*this)[1]--;
    return temp;
}



vect2 vect2::operator-() const
{
    return vect2(-(*this)[0], -(*this)[1]);
}  

bool vect2::operator==(const vect2& other) const
{
    return (*this)[0] == other[0] && (*this)[1] == other[1];
}

bool vect2::operator!=(const vect2& other) const
{
    return !(*this == other);
}

vect2 operator*(int scalar, const vect2& other)
{
    return other * scalar;
}
