#pragma once
#include <complex>

using namespace std;

template <class T>
T abs(T x) {
    return x > 0 ? x : -x;
}

template <class T>
int manhattan(complex<T> x) {
    return abs(real(x)) + abs(imag(x));
}

template <class T>
double argument(complex<T> x) {
    return arg(complex<double>(real(x), imag(x)));
}

namespace std {
template <class T>
struct hash<complex<T>> {
    size_t operator()(complex<T> const& s) const noexcept {
        size_t h1 = hash<T>{}(real(s));
        size_t h2 = hash<T>{}(imag(s));
        return h1 ^ (h2 << 1);
    }
};

template <class T, class U>
struct hash<pair<T, U>> {
    size_t operator()(pair<T, U> const& p) const noexcept {
        size_t h1 = hash<T>{}(p.first);
        size_t h2 = hash<U>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

template <class T>
bool operator<(const complex<T>& k1, const complex<T>& k2) {
    return make_pair(real(k1), imag(k1)) < make_pair(real(k2), imag(k2));
}

template <class T>
bool operator>(const complex<T>& k1, const complex<T>& k2) {
    return make_pair(real(k1), imag(k1)) > make_pair(real(k2), imag(k2));
}
}  // namespace std

template <typename T>
int sgn(T x, T y = T(0)) {
    return (y < x) - (x < y);  // sign(x - y)
}
