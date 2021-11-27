#include <gtest/gtest.h>
#include <memory>
#include <ostream>

#include "cache.h"

using Pool = cache::ObjectPool<cache::Person, 5, cache::releaser>;

TEST(ObjectPool, smoke_test)
{
    auto pool = Pool();
    ASSERT_TRUE(pool.get() != nullptr);
}

TEST(ObjectPool, objects_arent_deleted)
{
    auto pool = cache::ObjectPool<cache::Person, 5, cache::releaser>();
    auto person = pool.get();
    // get pointer to object, release it, ensure it has same adress
    ASSERT_TRUE(person);
    person.reset();

    struct TestOwner
    {
        std::shared_ptr<cache::Person> _person;
        TestOwner(Pool::Ptr person_)
        :   _person(person_)
        {}
    };

    std::vector<TestOwner*> testOwners;
    for (int i(0); i < 5; i++)
        testOwners.emplace_back(new TestOwner(pool.get()));
    for (auto owner : testOwners)
        LOG(owner);
    testOwners.clear();
    for (int i(0); i < 5; i++)
        testOwners.emplace_back(new TestOwner(pool.get()));
    for (auto owner : testOwners)
        LOG(&owner);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
