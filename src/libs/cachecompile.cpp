#include "cache.h"

namespace cache {
    template class ObjectPool<Person, 5, releaser>;
}
