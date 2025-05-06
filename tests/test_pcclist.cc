#include <gtest/gtest.h>
#include "../include/pcclist/pcclist.h"
#include <string>

// Helper: expect a bad_any_cast when casting wrong type
#define EXPECT_BAD_ANY_CAST(stmt)                                \
  try {                                                          \
    stmt;                                                        \
    FAIL() << "Expected std::bad_any_cast";                      \
  } catch (const std::bad_any_cast&) {                           \
  } catch (...) {                                                \
    FAIL() << "Expected std::bad_any_cast, got other exception"; \
  }

// 1) Test default construction and size/clear
TEST(ListBasic, DefaultConstruct) {
    PCCList::List L;
    EXPECT_EQ(L.size(), 0u);
    L.append(1);
    EXPECT_EQ(L.size(), 1u);
    L.clear();
    EXPECT_EQ(L.size(), 0u);
}

// 2) Test variadic constructor with mixed types
TEST(ListBasic, VariadicCtor) {
    PCCList::List L = { 10, "foo", 2.5 };
    EXPECT_EQ(L.size(), 3u);

    // operator[] retrieval
    int   i = L[0];              EXPECT_EQ(i, 10);
    std::string s = L[1];        EXPECT_EQ(s, "foo");
    double d = L[2];             EXPECT_DOUBLE_EQ(d, 2.5);
}

// 3) Test append of C-string becomes std::string
TEST(ListBasic, AppendCString) {
    PCCList::List L;
    L.append("bar");
    EXPECT_EQ(L.size(), 1u);
    // retrieving as std::string must succeed
    std::string s = L[0];
    EXPECT_EQ(s, "bar");
}

// 4) Test operator[] assignment
TEST(ListMutate, Assignment) {
    PCCList::List L = { 1, 2.0 };
    L[0] = 42;
    L[1] = 3.14;
    EXPECT_EQ(L[0], 42);
    EXPECT_DOUBLE_EQ(L[1], 3.14);
}

// 5) Test remove
TEST(ListMutate, Remove) {
    PCCList::List L = { 1, 2, 3 };
    L.remove(1);
    EXPECT_EQ(L.size(), 2u);
    EXPECT_EQ(L[0], 1);
    EXPECT_EQ(L[1], 3);
    EXPECT_THROW(L.remove(5), std::out_of_range);
}

// 6) Test insert
TEST(ListMutate, Insert) {
    PCCList::List L = { "a", "c" };
    L.insert(1, "b");
    EXPECT_EQ(L.size(), 3u);
    EXPECT_EQ(L[1], std::string("b"));
    EXPECT_THROW(L.insert(5, 10), std::out_of_range);
}

// 7) Test out-of-range operator[]
TEST(ListErrors, OutOfRange) {
    PCCList::List L = { 1 };
    EXPECT_THROW((void)L[1], std::out_of_range);
    EXPECT_THROW((void)L[100], std::out_of_range);
}

// 8) Test bad_any_cast on wrong-type retrieval
TEST(ListErrors, BadAnyCast) {
    PCCList::List L = { 1, 2.0 };
    EXPECT_BAD_ANY_CAST({ int x = L.get<int>(1); });
    EXPECT_BAD_ANY_CAST({ double d = L.get<double>(0); });
}

// 9) Test explicit get/try_get
TEST(ListAccess, GetAndTryGet) {
    PCCList::List L = { "hi", 7 };
    // correct
    EXPECT_EQ(L.get<std::string>(0), "hi");
    EXPECT_EQ(L.get<int>(1), 7);
    // try_get
    EXPECT_NE(L.try_get<std::string>(0), nullptr);
    EXPECT_EQ(*L.try_get<std::string>(0), "hi");
    EXPECT_EQ(L.try_get<double>(1), nullptr);
}

// 10) Test printing unprintable type
struct Pod { int a; };
TEST(ListIO, Unprintable) {
    PCCList::List L;
    L.append(Pod{5});
    std::ostringstream oss;
    oss << L[0];
    std::string out = oss.str();
    // should contain the type name
    EXPECT_NE(out.find("Pod"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}