#include <gtest/gtest.h>
#include "cache.h"
#include <ostream>


TEST(ObjectPool, smoke_test)
{
    cache::Person person = cache::Person();
    std::cout << "age: " << person.age << '\n';
    auto pool = cache::ObjectPool<cache::Person, 5>();
    pool.get();

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
