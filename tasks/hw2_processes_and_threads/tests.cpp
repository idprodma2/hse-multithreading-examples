#include <gtest/gtest.h>

#include "apply_function.hpp"

#include <cmath>
#include <vector>

namespace processes_and_threads::tests {
TEST(ApplyFunction, DoNothing) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    ApplyFunction<int>(data, [](int& x) { (void)x; }, 2);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(data, expected);
}

TEST(ApplyFunctionTest, EmptyData) {
    std::vector<int> data;
    EXPECT_NO_THROW(ApplyFunction<int>(data, [](int& x) { x++; }, 4));
}

TEST(ApplyFunctionTest, IntegerType) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    ApplyFunction<int>(data, [](int& x) { ++x; }, 2);
    std::vector<int> expected = {2, 3, 4, 5, 6};
    EXPECT_EQ(data, expected);
}

TEST(ApplyFunctionTest, StringType) {
    std::vector<std::string> stringData = {"1", "2", "3"};
    ApplyFunction<std::string>(stringData, [](std::string& x) { x += x; }, 2);
    std::vector<std::string> stringExpected = {"11", "22", "33"};
    EXPECT_EQ(stringData, stringExpected);
}

TEST(ApplyFunctionTest, DoubleType) {
    std::vector<double> doubleData = {1.5, 2.5, 3.5};
    ApplyFunction<double>(doubleData, [](double& x) { x = ceil(x); }, 2);
    std::vector<double> doubleExpected = {2, 3, 4};
    EXPECT_EQ(doubleData, doubleExpected);
}

struct MyStruct {
    int value_;
    MyStruct(int value) : value_(value) {}
    bool operator==(const MyStruct& other) const { return value_ == other.value_; }
    void editSelf() { ++value_; }
};

TEST(ApplyFunctionTest, CustomType) {
    std::vector<MyStruct> data = {
        MyStruct(1),
        MyStruct(2)
    };
    ApplyFunction<MyStruct>(data, [](MyStruct& elem) { elem.editSelf(); }, 2);
    std::vector<MyStruct> expected = {
        MyStruct(2),
        MyStruct(3)
    };
    EXPECT_EQ(data, expected);
}

TEST(ApplyFunctionTest, LargeData) {
    const int size = 100000;
    std::vector<int> data(size, 1);
    std::vector<int> expected(size, 2);
    
    ApplyFunction<int>(data, [](int& x) { ++x; }, 4);
    EXPECT_EQ(data, expected);
}
}  // namespace processes_and_threads::tests

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}