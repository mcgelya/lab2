#pragma once

#include <iostream>

#include "ienum.h"

template <class T>
class Sequence : public IEnumerable<T> {
public:
    virtual const T& GetFirst() = 0;
    virtual const T& GetLast() = 0;
    virtual const T& Get(int index) = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual int GetLength() const = 0;

    virtual int GetCapacity() const {
        return GetLength();
    }

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;

    virtual Sequence<T>* Instance() = 0;
    virtual Sequence<T>* Clone() = 0;

    Sequence<T>* Concat(Sequence<T>* seq) {
        if (seq == nullptr) {
            throw std::invalid_argument("Sequence::Concat() received nullptr as argument");
        }
        Sequence<T>* instance = this->Instance();
        for (IConstEnumerator<T>* it = seq->GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
            instance->Append(it->ConstDereference());
        }
        return instance;
    }

    friend std::ostream& operator<<(std::ostream& os, const Sequence<T>& v) {
        os << "{";
        for (IConstEnumerator<T>* it = v.GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
            os << it->ConstDereference();
            if (it->Index() + 1 < v.GetLength()) {
                os << ", ";
            }
        }
        os << "}";
        return os;
    }
};
