#pragma once

#include <cassert>
#include <stdexcept>
#include <string>

template <class T>
struct ListNode {
    T value;
    ListNode* next = nullptr;

    ListNode(T value) : value(value) {
    }

    ListNode<T>* NextNth(int n) {
        ListNode<T>* cur = this;
        for (int i = 0; i < n; ++i) {
            cur = cur->next;
        }
        return cur;
    }
};

template <class T>
class LinkedList {
public:
    LinkedList(const T* items, int count) {
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    LinkedList() {
    }

    LinkedList(const LinkedList<T>& l) {
        ListNode<T>* cur = l.first;
        for (int i = 0; i < l.size; ++i) {
            Append(cur->value);
            cur = cur->next;
        }
    }

    const T& GetFirst() const {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        return first->value;
    }

    const T& GetLast() const {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        return last->value;
    }

    const T& Get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(index) + " " + std::to_string(size));
        }
        return first->NextNth(index)->value;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(startIndex) + " " +
                                    std::to_string(size));
        }
        if (endIndex < 0 || endIndex >= size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(endIndex) + " " + std::to_string(size));
        }
        LinkedList<T>* res = new LinkedList<T>();
        ListNode<T>* cur = first->NextNth(startIndex);
        for (int i = startIndex; i <= endIndex; ++i) {
            res->Append(cur->value);
            cur = cur->next;
        }
        return res;
    }

    int GetLength() const {
        return size;
    }

    void Append(const T& item) {
        ListNode<T>* cur = new ListNode<T>(item);
        if (size == 0) {
            first = cur;
            last = cur;
            ++size;
            return;
        }
        last->next = cur;
        last = cur;
        ++size;
    }

    void Prepend(const T& item) {
        ListNode<T>* cur = new ListNode<T>(item);
        if (size == 0) {
            first = cur;
            last = cur;
            ++size;
            return;
        }
        cur->next = first;
        first = cur;
        ++size;
    }

    // Insert before index
    void InsertAt(const T& item, int index) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index is out of range: " + std::to_string(index) + " " + std::to_string(size));
        }
        if (index == size) {
            Append(item);
            return;
        }
        if (index == 0) {
            Prepend(item);
            return;
        }
        ListNode<T>* prev = first->NextNth(index - 1);
        ListNode<T>* next = prev->next;
        ListNode<T>* cur = new ListNode<T>(item);
        prev->next = cur;
        cur->next = next;
    }

    void Concat(LinkedList<T>* l) {
        if (l == nullptr) {
            throw std::invalid_argument("LinkedList::Concat() received nullptr as argument");
        }
        if (size == 0) {
            first = l->first;
            last = l->last;
            size = l->size;
            return;
        }
        last->next = l->first;
        size += l->size;
    }

    ListNode<T>* GetBegin() {
        return first;
    }

private:
    ListNode<T>* first = nullptr;
    ListNode<T>* last = nullptr;
    int size = 0;
};
