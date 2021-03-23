#include "cache.h"

// std
#include <memory>
#include <stdexcept>
#include <vector>
#include <functional>

#include "utils.h"


namespace cache
{

template<typename T, size_t size_>
ObjectPool<T, size_>::ObjectPool()
:   _size(size_)
,   _freeObjectRegistry()
,   _usedObjectRegistry()
{

}

template<typename T, size_t size_>
void
ObjectPool<T, size_>::initialise()
{
    _usedObjectRegistry.reserve(_size);
    _freeObjectRegistry.reserve(_size);
    for (size_t i(0); i < _size; i++)
    {
        _freeObjectRegistry.emplace_back();
    }
}

template<typename T, size_t size_>
size_t
ObjectPool<T, size_>::size()
{
    return _size;
}

template<typename T, size_t size_>
std::shared_ptr<T>
ObjectPool<T, size_>::get()
{
    size_t index(0);
    while (not _freeObjectRegistry[index])
    {
        ++index;
        if (index >= _size)
            throw std::out_of_range("Pool fully allocated");
    }
    std::shared_ptr<T> out = _freeObjectRegistry[index];
    _freeObjectRegistry[index] = nullptr;
    return out;
}



} // cache
