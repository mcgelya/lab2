#pragma once

#include <stdexcept>
#include <string>

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
            throw std::out_of_range("Index is out of range: " + std::to_string(index) + " " + std::to_string(size));
        }
        return data[index];
    }

    int GetSize() const {
        return size;
    }

    void Set(int index, const T& item) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(index) + " " + std::to_string(size));
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

    const T* GetConstBegin() {
        return data;
    }

private:
    T* data = nullptr;
    int size = 0;
};
