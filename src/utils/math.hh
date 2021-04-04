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
template <class T, class U>
struct hash<pair<T, U>> {
    size_t operator()(pair<T, U> const& p) const noexcept {
        size_t h1 = hash<T>{}(p.first);
        size_t h2 = hash<U>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

// Boost hash::combine function
template <>
struct hash<vector<int>> {
    size_t operator()(vector<int> const& vec) const noexcept {
        size_t seed = vec.size();
        for (auto& i : vec) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
}  // namespace std

template <typename T>
int sgn(T x, T y = T(0)) {
    return (y < x) - (x < y);  // sign(x - y)
}
