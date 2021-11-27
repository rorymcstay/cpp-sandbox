#include <gtest/gtest.h>>
#include <iostream>


TEST(simpleTest, smoke)
{
    std::out << "Hello World\n";
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

