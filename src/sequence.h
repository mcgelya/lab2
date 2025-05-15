#pragma once

#include <iostream>
#include "ienum.h"
#include "error.h"

template <class T, class I>
class Sequence : public IEnumerable<T, I> {
public:
    virtual const T& GetFirst() = 0;
    virtual const T& GetLast() = 0;
    virtual const T& Get(int index) = 0;

    virtual Sequence<T, I>* GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual int GetLength() const = 0;

    virtual Sequence<T, I>* Append(const T& item) = 0;
    virtual Sequence<T, I>* Prepend(const T& item) = 0;
    virtual Sequence<T, I>* InsertAt(const T& item, int index) = 0;

    virtual Sequence<T, I>* Instance() = 0;
    virtual Sequence<T, I>* Clone() = 0;

    template <class U>
    Sequence<T, I>* Concat(Sequence<T, U>* seq) {
        if (seq == nullptr) {
            throw ErrorInfo(ErrorCode::NullPointer, "Error: seq is null pointer.");
        }
        Sequence<T, I>* instance = this->Instance();
        for (T& item : *seq) {
            instance->Append(item);
        }
        return instance;
    }

    friend std::ostream& operator<<(std::ostream& os, const Sequence<T, I>& v) {
        os << "{";
        int ind = 0;
        for (const T& x : v) {
            os << x;
            if (ind + 1 < v.GetLength()) {
                os << ", ";
            }
            ++ind;
        }
        os << "}";
        return os;
    }
};
