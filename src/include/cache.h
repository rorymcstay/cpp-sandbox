#ifndef CACHE_H
#define CACHE_H

#include <memory>
#include <vector>
#include <string>




namespace cache 
{

struct Person
{
    std::string name;
    int age;
};

template<typename T, size_t size_>
class ObjectPool
{
public:
    ObjectPool();
    ~ObjectPool() {};
    std::shared_ptr<T> get();
    size_t size();

private:

    size_t                          _size;
    std::vector<std::shared_ptr<T>> _freeObjectRegistry;
    std::vector<std::shared_ptr<T>> _usedObjectRegistry;
    void initialise();

};


template class ObjectPool<Person, 5>;

} // cache

#endif

