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

namespace std {
template <class T>
struct hash<complex<T>> {
    size_t operator()(complex<T> const& s) const noexcept {
        size_t h1 = hash<T>{}(real(s));
        size_t h2 = hash<T>{}(imag(s));
        return h1 ^ (h2 << 1);
    }
};
}  // namespace std
