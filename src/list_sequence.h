#pragma once

#include <cassert>

#include "ienum.h"
#include "linked_list.h"
#include "sequence.h"

template <class T>
class ListSequenceIterator : public IEnumerator<T> {
public:
    ListSequenceIterator(ListNode<T>* it) : it(it) {
    }

    bool IsEnd() const override {
        return it == nullptr;
    }

    void MoveNext() override {
        assert(it != nullptr);
        it = it->next;
        ++index;
    }

    T& Dereference() override {
        assert(it != nullptr);
        return it->value;
    }

    int Index() const override {
        return index;
    }

private:
    ListNode<T>* it;

    int index = 0;
};

template <class T>
class ListSequenceConstIterator : public IConstEnumerator<T> {
public:
    ListSequenceConstIterator(ListNode<T>* it) : it(it) {
    }

    bool IsEnd() const override {
        return it == nullptr;
    }

    void MoveNext() override {
        assert(it != nullptr);
        it = it->next;
        ++index;
    }

    const T& ConstDereference() const override {
        assert(it != nullptr);
        return it->value;
    }

    int Index() const override {
        return index;
    }

private:
    ListNode<T>* it;

    int index = 0;
};

template <class T>
class ListSequence : public Sequence<T> {
public:
    ListSequence(const T* items, int count) {
        data = new LinkedList<T>(items, count);
    }

    ListSequence(const LinkedList<T>& l) {
        data = new LinkedList<T>(l);
    }

    ListSequence() {
        data = new LinkedList<T>();
    }

    const T& GetFirst() override {
        return data->GetFirst();
    }

    const T& GetLast() override {
        return data->GetLast();
    }

    const T& Get(int index) override {
        return data->Get(index);
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        ListSequence<T>* res = new ListSequence(*data->GetSubList(startIndex, endIndex));
        return res;
    }

    int GetLength() const override {
        return data->GetLength();
    }

    ListSequence<T>* Append(const T& item) override {
        ListSequence<T>* instance = Instance();
        instance->data->Append(item);
        return instance;
    }

    ListSequence<T>* Prepend(const T& item) override {
        ListSequence<T>* instance = Instance();
        instance->data->Prepend(item);
        return instance;
    }

    ListSequence<T>* InsertAt(const T& item, int index) override {
        ListSequence<T>* instance = Instance();
        instance->data->InsertAt(item, index);
        return instance;
    }

    ListSequence<T>* Instance() override {
        return this;
    }

    ListSequence<T>* Clone() override {
        ListSequence<T>* res = new ListSequence<T>(*data);
        return res;
    }

    IEnumerator<T>* GetEnumerator() override {
        return new ListSequenceIterator<T>(data->GetBegin());
    }

    IConstEnumerator<T>* GetConstEnumerator() const override {
        return new ListSequenceConstIterator<T>(data->GetBegin());
    }

protected:
    LinkedList<T>* data;
};

template <class T>
class ImmutableListSequence : public ListSequence<T> {
    using ListSequence<T>::ListSequence;

    ListSequence<T>* Clone() override {
        ListSequence<T>* res = new ImmutableListSequence<T>(*this->data);
        return res;
    }

    ListSequence<T>* Instance() override {
        return this->Clone();
    }
};

template <class T>
class MutableListSequence : public ListSequence<T> {
    using ListSequence<T>::ListSequence;
};
