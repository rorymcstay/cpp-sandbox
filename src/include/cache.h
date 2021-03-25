#ifndef CACHE_H
#define CACHE_H

#include <memory>
#include <vector>
#include <string>
#include <functional>

#include "utils.h"


namespace cache 
{

struct Person
{
    std::string name;
    int age;
    Person()
    :   name("")
    ,   age(0)
    {}
};

struct releaser
{
    void operator() (Person* person_)
    {
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

    Deleter<T>          _releaser; 
    size_t              _size;
    std::vector<Ptr>    _freeObjectRegistry;
    std::vector<Ptr>    _usedObjectRegistry;
private:
    void initialise();
    void replace(T* ptr_, int pos );

};

template class ObjectPool<Person, 5, releaser>;

} // cache

#endif

