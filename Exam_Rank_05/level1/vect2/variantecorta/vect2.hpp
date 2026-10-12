#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class vect2 {
	int v[2];

public:
	vect2(int x = 0, int y = 0) { v[0] = x; v[1] = y; }

	int &operator[](int i) { return v[i]; }
	const int &operator[](int i) const { return v[i]; }

	vect2 &operator+=(const vect2 &o) { v[0] += o[0]; v[1] += o[1]; return *this; }
	vect2 &operator-=(const vect2 &o) { v[0] -= o[0]; v[1] -= o[1]; return *this; }
	vect2 operator+(const vect2 &o) const { return vect2(*this) += o; }
	vect2 operator-(const vect2 &o) const { return vect2(*this) -= o; }

	vect2 &operator*=(int s) { v[0] *= s; v[1] *= s; return *this; }
	vect2 operator*(int s) const { return vect2(*this) *= s; }

	vect2 &operator++() { ++v[0]; ++v[1]; return *this; }
	vect2 operator++(int) { vect2 t(*this); ++(*this); return t; }
	vect2 &operator--() { --v[0]; --v[1]; return *this; }
	vect2 operator--(int) { vect2 t(*this); --(*this); return t; }

	vect2 operator-() const { return vect2(-v[0], -v[1]); }

	bool operator==(const vect2 &o) const { return v[0] == o[0] && v[1] == o[1]; }
	bool operator!=(const vect2 &o) const { return !(*this == o); }
};

inline vect2 operator*(int s, const vect2 &o) { return o * s; }
inline std::ostream &operator<<(std::ostream &os, const vect2 &o) { return os << "{" << o[0] << ", " << o[1] << "}"; }

#endif
