#pragma once

#include "error.h"

template <class T>
class DynamicArray {
public:
    DynamicArray(const T* items, int count) : size(count) {
        data = new T[size]();
        for (int i = 0; i < size; ++i) {
            data[i] = items[i];
        }
    }

    DynamicArray() {
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(int size) : size(size) {
        if (size != 0) {
            data = new T[size]();
        }
    }

    DynamicArray(const DynamicArray<T>& v) : size(v.size) {
        if (size != 0) {
            data = new T[size]();
            for (int i = 0; i < size; ++i) {
                data[i] = v.data[i];
            }
        }
    }

    const T& Get(int index) const {
        if (index < 0 || index >= size) {
            throw ErrorInfo(ErrorCode::IndexOutOfRange, "Error: Index is out of range.");
        }
        return data[index];
    }

    int GetSize() const {
        return size;
    }

    void Set(int index, const T& item) {
        if (index < 0 || index >= size) {
            throw ErrorInfo(ErrorCode::IndexOutOfRange, "Error: Index is out of range.");
        }
        data[index] = item;
    }

    void Resize(int newSize) {
        if (newSize < size) {
            size = newSize;
            return;
        }
        T* newData = new T[newSize]();
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

    T* GetBegin() {
        return data;
    }

    T* GetEnd() {
        return data + size;
    }

private:
    T* data = nullptr;
    int size = 0;
};
