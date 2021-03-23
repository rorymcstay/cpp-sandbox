#include "cache.h"

// std
#include <memory>
#include <stdexcept>
#include <vector>
#include <functional>

#include "utils.h"


namespace cache
{

template<typename T, size_t size_, typename Releaser>
ObjectPool<T, size_, Releaser>::ObjectPool()
:   _size(size_)
,   _freeObjectRegistry()
,   _usedObjectRegistry()
{
    initialise();
}

template<typename T, size_t size_, typename Releaser>
void
ObjectPool<T, size_, Releaser>::initialise()
{
    _usedObjectRegistry.reserve(_size);
    _freeObjectRegistry.reserve(_size);
    for (size_t i(0); i < _size; i++)
    {
        _freeObjectRegistry.emplace_back(new T(), Releaser());
    }
}

template<typename T, size_t size_, typename Releaser>
size_t
ObjectPool<T, size_, Releaser>::size()
{
    return _size;
}

template<typename T, size_t size_, typename Releaser>
std::shared_ptr<T>
ObjectPool<T, size_, Releaser>::get()
{
    size_t index(0);
    while (!_freeObjectRegistry[index].get())
    {
        ++index;
        if (index >= _size)
            throw std::out_of_range("Pool fully allocated");
    }
    Ptr out = _freeObjectRegistry[index];
    _freeObjectRegistry[index] = nullptr;
    return out;
}

} // cache
