cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER /usr/bin/g++-8)

add_compile_options(-DBOOST_LOG_DYN_LINK 
    -Wall -Wextra -Wpedantic  -Werror -lboost_log 
    -lpthread -lboost_log_setup -ljsoncpp -std=gnu++2a
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package (Threads)
find_package (Boost 1.55.0 REQUIRED COMPONENTS program_options log log_setup system filesystem)


include_directories(
    ${Boost_INCLUDE_DIR}
)

message(jsoncpp_LIBRARY = ${JSONCPP_LIBRARIES})

message( "include dirs json ${JSONCPP_INCLUDE_DIRS}")

add_subdirectory(src)
add_subdirectory(test)

add_executable(tertiary_func src/tertiary_func.cpp)
add_executable(main src/main.cpp)

set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS
    tertiary_func
    main
    # libs
    # tests
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

