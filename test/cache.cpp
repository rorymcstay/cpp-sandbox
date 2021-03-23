#include <gtest/gtest.h>
#include "cache.h"
#include <ostream>


TEST(ObjectPool, smoke_test)
{
    cache::Person person = cache::Person();
    std::cout << "age: " << person.age << '\n';
    auto pool = cache::ObjectPool<cache::Person, 5, cache::releaser>();
    ASSERT_TRUE(pool.get() != nullptr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
