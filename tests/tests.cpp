#include <catch2/catch_test_macros.hpp>
#include "../src/list_sequence.h"
#include "../src/array_sequence.h"

#include <iostream>

TEST_CASE("ListSequence append") {
    ListSequence<int>* l = new ListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    l->Append(1);
    l->Append(2);
    REQUIRE(l->Get(4) == 1);
    REQUIRE(l->Get(5) == 2);
}

TEST_CASE("ImmutableListSequence append") {
    ListSequence<int>* l = new ImmutableListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    ListSequence<int>* l1 = l->Append(1);
    REQUIRE(l->GetLength() == 4);
    REQUIRE(l1->GetLength() == 5);
    REQUIRE(l1->GetLast() == 1);

    ListSequence<int>* l2 = l1->Append(0);
    REQUIRE(l1->GetLength() == 5);
    REQUIRE(l1->GetLast() == 1);
    REQUIRE(l2->GetLength() == 6);
    REQUIRE(l2->GetLast() == 0);
}

TEST_CASE("ArraySequence append") {
    ArraySequence<int>* a = new ArraySequence<int>(new int[]{1, 2, 3, 4}, 4);
    a->Append(1);
    a->Append(2);
    REQUIRE(a->Get(4) == 1);
    REQUIRE(a->Get(5) == 2);
    REQUIRE(a->GetCapacity() == 8);
}

TEST_CASE("ImmutableArraySequence append") {
    ArraySequence<int>* a = new ImmutableArraySequence<int>(new int[]{1, 2, 3, 4}, 4);
    ArraySequence<int>* a1 = a->Append(1);
    REQUIRE(a->GetLength() == 4);
    REQUIRE(a1->GetLength() == 5);
    REQUIRE(a1->GetLast() == 1);

    ArraySequence<int>* a2 = a1->Append(0);
    REQUIRE(a1->GetLength() == 5);
    REQUIRE(a1->GetLast() == 1);
    REQUIRE(a2->GetLength() == 6);
    REQUIRE(a2->GetLast() == 0);
}

TEST_CASE("ListSequence Prepend") {
    ListSequence<int>* l = new ListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    l->Prepend(-1);
    l->Prepend(0);
    REQUIRE(l->GetLength() == 6);
    REQUIRE(l->Get(0) == 0);
    REQUIRE(l->Get(1) == -1);
}

TEST_CASE("ImmutableListSequenc Prepend") {
    ListSequence<int>* l = new ImmutableListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    ListSequence<int>* l1 = l->Prepend(0);
    REQUIRE(l->GetLength() == 4);
    REQUIRE(l1->GetLength() == 5);
    REQUIRE(l1->GetFirst() == 0);
}

TEST_CASE("ArraySequence Prepend") {
    ArraySequence<int>* a = new ArraySequence<int>(new int[]{1, 2, 3, 4}, 4);
    a->Prepend(-1);
    a->Prepend(0);
    REQUIRE(a->GetLength() == 6);
    REQUIRE(a->Get(0) == 0);
    REQUIRE(a->Get(1) == -1);
    REQUIRE(a->GetCapacity() == 8);
}

TEST_CASE("ImmutableArraySequence Prepend") {
    ArraySequence<int>* a = new ImmutableArraySequence<int>(new int[]{1, 2, 3, 4}, 4);
    ArraySequence<int>* a1 = a->Prepend(1);
    REQUIRE(a->GetLength() == 4);
    REQUIRE(a1->GetLength() == 5);
    REQUIRE(a1->GetFirst() == 1);

    ArraySequence<int>* a2 = a1->Prepend(0);
    REQUIRE(a1->GetLength() == 5);
    REQUIRE(a1->GetFirst() == 1);
    REQUIRE(a2->GetLength() == 6);
    REQUIRE(a2->GetFirst() == 0);
}

TEST_CASE("ListSequence concat") {
    ListSequence<int>* a = new ListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    ListSequence<int>* b = new ListSequence<int>(new int[]{5, 6, 7, 8}, 4);
    a->Concat(b);
    REQUIRE(a->GetLength() == 8);
    for (int i = 0; i < 8; ++i) {
        REQUIRE(a->Get(i) == i + 1);
    }
    REQUIRE(b->GetLength() == 4);
    for (int i = 0; i < 4; ++i) {
        REQUIRE(b->Get(i) == 5 + i);
    }
}

TEST_CASE("ArraySequence concat") {
    ArraySequence<int>* a = new ArraySequence<int>(new int[]{1, 2, 3}, 3);
    ArraySequence<int>* b = new ArraySequence<int>(new int[]{4, 5, 6}, 3);
    a->Concat(b);
    REQUIRE(a->GetLength() == 6);
    for (int i = 0; i < 6; ++i) {
        REQUIRE(a->Get(i) == 1 + i);
    }
    REQUIRE(b->GetLength() == 3);
    for (int i = 0; i < 3; ++i) {
        REQUIRE(b->Get(i) == 4 + i);
    }
}

TEST_CASE("ListSequence enumerable") {
    ListSequence<int>* a = new ListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    for (IEnumerator<int>* it = a->GetEnumerator(); !it->IsEnd(); it->MoveNext()) {
        ++it->Dereference();
    }
    int j = 2;
    for (IConstEnumerator<int>* it = a->GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
        int val = it->ConstDereference();
        REQUIRE(val == j);
        ++j;
    }
    // compiling
    const ListSequence<int>* b = new ListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    IConstEnumerator<int>* it = b->GetConstEnumerator();
    for (IConstEnumerator<int>* it = b->GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
        std::cout << it->ConstDereference() << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("ArraySequence enumerable") {
    ArraySequence<int>* a = new ArraySequence<int>(new int[]{1, 2, 3}, 3);
    for (IEnumerator<int>* it = a->GetEnumerator(); !it->IsEnd(); it->MoveNext()) {
        ++it->Dereference();
    }
    int j = 2;
    for (IConstEnumerator<int>* it = a->GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
        int val = it->ConstDereference();
        REQUIRE(val == j);
        ++j;
    }
    REQUIRE(j == 5);
    // compiling
    const ArraySequence<int>* b = new ArraySequence<int>(new int[]{1, 2, 3}, 3);
    IConstEnumerator<int>* it = b->GetConstEnumerator();
    for (IConstEnumerator<int>* it = b->GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
        std::cout << it->ConstDereference() << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("ArraySequence: Index out of range") {
    ArraySequence<int>* a = new ArraySequence<int>(new int[]{1, 2, 3, 4}, 4);
    REQUIRE_THROWS(a->Get(4));
    REQUIRE_THROWS(a->Get(-1));
}

TEST_CASE("ListSequence: Index out of range") {
    ListSequence<int>* a = new ListSequence<int>(new int[]{1, 2, 3, 4}, 4);
    REQUIRE_THROWS(a->Get(4));
    REQUIRE_THROWS(a->Get(-1));
}
