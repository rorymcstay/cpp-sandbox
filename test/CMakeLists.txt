find_package(GTest REQUIRED)
include_directories(
    ${GTEST_INCLUDE_DIRS}
)

add_executable(cache_test 
    cache.cpp
)
target_link_libraries(cache_test 
    LINK_PUBLIC
    gtest
    pthread
    caches
)

install(TARGETS
    cache_test
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
