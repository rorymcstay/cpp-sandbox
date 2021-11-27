cmake_minimum_required(VERSION 3.20)
project(cpp_sandbox)

add_compile_options(-DBOOST_LOG_DYN_LINK 
    -Wall -Wextra -Wpedantic  
    #-lboost_log -lpthread -lboost_log_setup -ljsoncpp 
    -std=c++20
    # required for clang
    -Wno-error=unused-command-line-argument
    -Wno-unused-command-line-argument
    -Wgcc-compat
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package (Threads)
find_package(benchmark REQUIRED)
find_package (Boost 1.55.0 REQUIRED COMPONENTS program_options log log_setup system filesystem)
#add_subdirectory(abseil-cpp)
#include_directories(abseil-cpp/)


include_directories(
    ${Boost_INCLUDE_DIR}
)

message(jsoncpp_LIBRARY = ${JSONCPP_LIBRARIES})

message( "include dirs json ${JSONCPP_INCLUDE_DIRS}")

add_subdirectory(src)
add_subdirectory(test)

add_executable(tertiary_func app/tertiary_func.cpp)
add_executable(btree app/btree.cpp)
add_executable(bench app/bench.cpp)
target_link_libraries(bench benchmark pthread)


#add_executable(strings app/strings.cpp)
#target_link_libraries(strings LINK_PUBLIC gtest pthread absl::strings)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(vector app/vector.cpp)
target_link_libraries(vector LINK_PUBLIC gtest pthread)

add_executable(sort app/sort.cpp)
target_link_libraries(sort LINK_PUBLIC gtest pthread)


#add_executable(absl app/absl.cpp)
#target_link_libraries(absl LINK_PUBLIC gtest pthread
#    absl::strings
#    absl::random_random
#)

#add_executable(divide app/divide.cpp)
#target_link_libraries(divide gtest pthread)

add_library(bitmex-rest /home/rory/dev/api-connectors/auto-generated/cpprest/*.cpp)



#add_executable(list app/list.cpp)
#target_link_libraries(list LINK_PUBLIC)

install(TARGETS
    tertiary_func
    btree
    bench
    sort
    #    strings
    #absl
    vector
    
    # libs
    # tests
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

