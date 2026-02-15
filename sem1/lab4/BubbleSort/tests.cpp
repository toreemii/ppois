#include <gtest/gtest.h>
#include "BubbleSort.h"
#include "Student.h"
#include "Product.h"
#include "Functions.h"
#include <vector>
#include <string>

TEST(BubbleSortTest, BuiltInTypes_IntArray)
{
    int arr[] = {5, 2, 8, 1, 9, 3};
    int expected[] = {1, 2, 3, 5, 8, 9};
    bubbleSort(arr);
    EXPECT_TRUE(isSorted(arr));
    EXPECT_EQ(std::vector<int>(std::begin(arr), std::end(arr)),
              std::vector<int>(std::begin(expected), std::end(expected)));
}

TEST(BubbleSortTest, BuiltInTypes_DoubleArray)
{
    double arr[] = {3.14, 1.41, 2.71, 0.57, 4.67};
    bubbleSort(arr);
    EXPECT_TRUE(isSorted(arr));
}

TEST(BubbleSortTest, BuiltInTypes_StringVector)
{
    std::vector<std::string> vec = {"banana", "apple", "cherry", "date", "avocado"};
    std::vector<std::string> expected = {"apple", "avocado", "banana", "cherry", "date"};
    bubbleSort(vec);
    EXPECT_EQ(vec, expected);
    EXPECT_TRUE(isSorted(vec));
}

TEST(BubbleSortTest, CustomClass_StudentByName)
{
    Student students[] = {
        Student("Ivan", 20, 4.5),
        Student("Anna", 19, 4.8),
        Student("Vika", 21, 4.2),
        Student("Maria", 20, 4.9),
        Student("Gena", 22, 4.1)};
    bubbleSort(students);
    EXPECT_TRUE(isSorted(students));
    EXPECT_EQ(students[0].getName(), "Anna");
    EXPECT_EQ(students[4].getName(), "Vika");
}

TEST(BubbleSortTest, CustomClass_ProductByPrice)
{
    std::vector<Product> products = {
        Product("Laptop", 999.99, 10),
        Product("Mouse", 25.50, 50),
        Product("Keyboard", 75.00, 30),
        Product("Monitor", 299.99, 15),
        Product("Headphones", 49.99, 25)};
    bubbleSort(products);
    EXPECT_TRUE(isSorted(products));
    EXPECT_EQ(products[0].getPrice(), 25.50);
    EXPECT_EQ(products[4].getPrice(), 999.99);
}

TEST(BubbleSortTest, EdgeCases_EmptyVector)
{
    std::vector<int> vec;
    bubbleSort(vec);
    EXPECT_TRUE(isSorted(vec));
}

TEST(BubbleSortTest, EdgeCases_SingleElement)
{
    int arr[] = {42};
    bubbleSort(arr);
    EXPECT_TRUE(isSorted(arr));
}

TEST(BubbleSortTest, EdgeCases_AlreadySorted)
{
    int arr[] = {1, 2, 3, 4, 5};
    bubbleSort(arr);
    EXPECT_TRUE(isSorted(arr));
}

TEST(BubbleSortTest, EdgeCases_ReverseSorted)
{
    int arr[] = {5, 4, 3, 2, 1};
    bubbleSort(arr);
    EXPECT_TRUE(isSorted(arr));
}

TEST(BubbleSortTest, Iterators_PartialSort)
{
    std::vector<int> numbers = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    bubbleSort(numbers.begin() + 2, numbers.begin() + 7);
    EXPECT_TRUE(isSorted(numbers.begin() + 2, numbers.begin() + 7));
    EXPECT_EQ(numbers[2], 3);
    EXPECT_EQ(numbers[6], 7);
}

TEST(BubbleSortTest, OriginalCase_ArrayAndVector)
{
    int *arr = new int[11]{1, 2, 4, 6, 3, 8, 2, 5, 2, 3, 2};
    std::vector<int> vec = {1, 7, 4, 2, 67, 1};

    bubbleSort(arr, arr + 11);
    bubbleSort(vec);

    EXPECT_TRUE(isSorted(arr, arr + 11));
    EXPECT_TRUE(isSorted(vec));

    delete[] arr;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}