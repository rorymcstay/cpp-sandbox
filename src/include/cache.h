#ifndef CACHE_H
#define CACHE_H

#include <memory>
#include <vector>
#include <string>
#include <functional>

#include "utils.h"

static int people_created(0);

namespace cache 
{

struct Person
{
    std::string name;
    int age;
    Person()
    :   name("")
    ,   age(0)
    {
        LOG("people_created=" << ++people_created);
    }
};

struct releaser
{
    void operator() (Person* person_)
    {
        LOG("Releasing person");
        person_->name = "";
        person_->age = 0;
    }
};


template<class T> using Deleter = std::function<void(T*)>;

std::function<void(Person*)> deleter = [](Person* person_) { person_->age = 0; person_->name = ""; };

template<typename T, size_t size_, typename Releaser>
class ObjectPool
{
public:
    using Ptr = std::shared_ptr<T>;
    ObjectPool();
    ~ObjectPool() {};
    std::shared_ptr<T> get();
    size_t size();

private:

    Releaser            _releaser; 
    size_t              _size;
    std::vector<Ptr>    _freeObjectRegistry;
    std::vector<Ptr>    _usedObjectRegistry;
private:
    void initialise();

};

template class ObjectPool<Person, 5, releaser>;

} // cache

#endif

