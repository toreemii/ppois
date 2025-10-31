#include <gtest/gtest.h>
#include "PatienceSort.h"
#include "Student.h"
#include "Product.h"
#include <vector>
#include <algorithm>

TEST(PatienceSortTest, IntVector)
{
    std::vector<int> v = {5, 3, 8, 1, 9, 2};
    patienceSort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(PatienceSortTest, IntArray)
{
    int arr[] = {7, 1, 4, 2};
    patienceSort(arr);
    EXPECT_TRUE(std::is_sorted(std::begin(arr), std::end(arr)));
}

TEST(PatienceSortTest, EmptyVector)
{
    std::vector<int> v;
    patienceSort(v);
    EXPECT_TRUE(v.empty());
}

TEST(PatienceSortTest, SingleElement)
{
    std::vector<int> v = {42};
    patienceSort(v);
    EXPECT_EQ(v[0], 42);
}

TEST(PatienceSortTest, AlreadySorted)
{
    std::vector<int> v = {1, 2, 3, 4};
    patienceSort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(PatienceSortTest, StudentByGrade)
{
    std::vector<Student> students = {
        Student("Ivan", 75.0),
        Student("Anna", 95.0),
        Student("Vika", 88.0),
        Student("Gena", 60.0)};
    patienceSort(students);
    EXPECT_EQ(students[0].getName(), "Gena");
    EXPECT_EQ(students[3].getName(), "Anna");
}

TEST(PatienceSortTest, ProductByPrice)
{
    std::vector<Product> products = {
        Product("Laptop", 999.99, 5),
        Product("Mouse", 25.50, 100),
        Product("Keyboard", 75.00, 30)};
    patienceSort(products);
    EXPECT_EQ(products[0].getPrice(), 25.50);
    EXPECT_EQ(products[2].getPrice(), 999.99);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}