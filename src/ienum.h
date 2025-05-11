#pragma once

template <class T, class I>
class IEnumerator {
public:
    IEnumerator(const I& it) : it(it) {
    }

    bool operator!=(const IEnumerator<T, I>& other) const {
        return it.NotEqual(other.it);
    }

    T& operator*() {
        return it.Dereference();
    }

    IEnumerator<T, I>& operator++() {
        it.MoveNext();
        return *this;
    }

    I it;
};

template <class T, class I>
class IEnumeratorConst {
public:
    IEnumeratorConst(const I& it) : it(it) {
    }

    bool operator!=(const IEnumeratorConst<T, I>& other) const {
        return it.NotEqual(other.it);
    }

    const T& operator*() const {
        return it.ConstDereference();
    }

    IEnumeratorConst<T, I>& operator++() {
        it.MoveNext();
        return *this;
    }

    I it;
};

template <class T, class I>
class IEnumerable {
public:
    virtual IEnumerator<T, I> begin() = 0;
    virtual IEnumerator<T, I> end() = 0;

    virtual IEnumeratorConst<T, I> begin() const = 0;
    virtual IEnumeratorConst<T, I> end() const = 0;
};
