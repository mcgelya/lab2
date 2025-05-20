#pragma once

#include <cassert>

#include "dynamic_array.h"
#include "ienum.h"
#include "sequence.h"

template <class T>
class ArraySequenceIterator : public IEnumerator<T> {
public:
    ArraySequenceIterator(T* it, int size) : it(it), size(size) {
    }

    bool IsEnd() const override {
        return index == size;
    }

    void MoveNext() override {
        assert(index < size);
        ++it;
        ++index;
    }

    T& Dereference() override {
        assert(index < size);
        return *it;
    }

    int Index() const override {
        return index;
    }

private:
    T* it;
    const int size;
    int index = 0;
};

template <class T>
class ArraySequenceConstIterator : public IConstEnumerator<T> {
public:
    ArraySequenceConstIterator(T* it, int size) : it(it), size(size) {
    }

    bool IsEnd() const override {
        return index == size;
    }

    void MoveNext() override {
        assert(index < size);
        ++it;
        ++index;
    }

    const T& ConstDereference() const override {
        assert(index < size);
        return *it;
    }

    int Index() const override {
        return index;
    }

private:
    T* it;
    const int size;
    int index = 0;
};

template <class T>
class ArraySequence : public Sequence<T> {
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

    ArraySequence(const ArraySequence<T>* a) {
        data = new DynamicArray<T>(*a->data);
        size = a->size;
        capacity = a->capacity;
    }

    ArraySequence() {
        data = new DynamicArray<T>(1);
    }

    const T& GetFirst() override {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        return data->Get(0);
    }

    const T& GetLast() override {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        return data->Get(size - 1);
    }

    const T& Get(int index) override {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(index) + " " + std::to_string(size));
        }
        return data->Get(index);
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || startIndex >= size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(startIndex) + " " +
                                    std::to_string(size));
        }
        if (endIndex < 0 || endIndex >= size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(endIndex) + " " + std::to_string(size));
        }
        T* start = data->GetBegin() + startIndex;
        int sz = endIndex - startIndex + 1;
        ArraySequence<T>* res = new ArraySequence(start, sz);
        return res;
    }

    int GetLength() const override {
        return size;
    }

    int GetCapacity() const override {
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
        ArraySequence<T>* res = new ArraySequence<T>(this);
        return res;
    }

    IEnumerator<T>* GetEnumerator() override {
        return new ArraySequenceIterator<T>(data->GetBegin(), size);
    }

    IConstEnumerator<T>* GetConstEnumerator() const override {
        return new ArraySequenceConstIterator<T>(data->GetBegin(), size);
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
        assert(size <= capacity);
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
        ArraySequence<T>* res = new ImmutableArraySequence<T>(this);
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
