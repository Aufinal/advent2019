#include <unordered_set>

template <class T>
T intersect(const T &a, const T &b) {
    T res;
    for (auto elt : a)
        if (b.count(elt)) res.insert(elt);

    return res;
}

template <class T>
T merge(const T &a, const T &b) {
    T res(a);
    res.insert(b.cbegin(), b.cend());
    return res;
}