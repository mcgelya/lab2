#pragma once

#include <cassert>
#include "ienum.h"
#include "dynamic_array.h"
#include "sequence.h"

template <class T>
class ArraySequenceIterator {
public:
    ArraySequenceIterator(T* it) : it(it) {
    }

    bool NotEqual(const ArraySequenceIterator<T>& other) const {
        return it != other.it;
    }

    T& Dereference() {
        return *it;
    }

    void MoveNext() {
        ++it;
    }

private:
    T* it;
};

template <class T>
class ArraySequence : public Sequence<T, ArraySequenceIterator<T>> {
public:
    ArraySequence(const T* items, int count) {
        data = new DynamicArray<T>(items, count);
        size = count;
        capacity = count;
    }

    ArraySequence(const DynamicArray<T>& a) {
        data = new DynamicArray<T>(a);
        size = a.GetSize();
        capacity = a.GetSize();
    }

    ArraySequence() {
        data = new DynamicArray<T>(1);
    }

    const T& GetFirst() override {
        if (size == 0) {
            throw ErrorInfo(ErrorCode::IndexOutOfRange, "Error: Array is empty.");
        }
        return data->Get(0);
    }

    const T& GetLast() override {
        if (size == 0) {
            throw ErrorInfo(ErrorCode::IndexOutOfRange, "Error: Array is empty.");
        }
        return data->Get(size - 1);
    }

    const T& Get(int index) override {
        if (index < 0 || index >= size) {
            throw ErrorInfo(ErrorCode::IndexOutOfRange, "Error: Index is out of range.");
        }
        return data->Get(index);
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || startIndex >= size || endIndex < 0 || endIndex >= size) {
            throw ErrorInfo(ErrorCode::IndexOutOfRange, "Error: Index is out of range.");
        }
        T* start = data->GetBegin() + startIndex;
        int sz = endIndex - startIndex + 1;
        ArraySequence<T>* res = new ArraySequence(start, sz);
        return res;
    }

    int GetLength() const override {
        return size;
    }

    int GetCapacity() const {  // for tests
        return capacity;
    }

    ArraySequence<T>* Append(const T& item) override {
        ArraySequence<T>* instance = Instance();
        instance->PushBack(item);
        return instance;
    }

    ArraySequence<T>* Prepend(const T& item) override {
        ArraySequence<T>* instance = Instance();
        instance->Insert(item, 0);
        return instance;
    }

    ArraySequence<T>* InsertAt(const T& item, int index) override {
        ArraySequence<T>* instance = Instance();
        instance->Insert(item, index);
        return instance;
    }

    ArraySequence<T>* Instance() override {
        return this;
    }

    ArraySequence<T>* Clone() override {
        ArraySequence<T>* res = new ArraySequence<T>(*data);
        return res;
    }

    IEnumerator<T, ArraySequenceIterator<T>> begin() override {
        return ArraySequenceIterator<T>(data->GetBegin());
    }

    IEnumerator<T, ArraySequenceIterator<T>> end() override {
        return ArraySequenceIterator<T>(data->GetEnd());
    }

protected:
    DynamicArray<T>* data;
    int size = 0;
    int capacity = 1;

    void PushBack(const T& item) {
        assert(size <= capacity);
        if (size == capacity) {
            data->Resize(capacity * 2);
            capacity *= 2;
        }
        data->Set(size, item);
        ++size;
    }

    void Insert(const T& item, int index) {
        if (size == capacity) {
            data->Resize(capacity * 2);
            capacity *= 2;
        }
        for (int i = size - 1; i >= index; --i) {
            T cur = data->Get(i);
            data->Set(i + 1, cur);
        }
        data->Set(index, item);
        ++size;
    }
};

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
    using ArraySequence<T>::ArraySequence;

    ArraySequence<T>* Clone() override {
        ArraySequence<T>* res = new ImmutableArraySequence<T>(*this->data);
        return res;
    }

    ArraySequence<T>* Instance() override {
        return this->Clone();
    }
};

template <class T>
class MutableArraySequence : public ArraySequence<T> {
    using ArraySequence<T>::ArraySequence;
};
