########
# Caches
########

set(INCLUDE_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(caches SHARED libs/cache.cpp)
target_include_directories(caches PUBLIC ${INCLUDE_SOURCES} )



install(TARGETS
    # libs
    caches
    # tests
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
