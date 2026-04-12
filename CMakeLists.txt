cmake_minimum_required(VERSION 3.15)
project(LRUCache CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# Build the cache library
add_library(lru_cache_lib 
    src/lru_cache.cpp
)

target_include_directories(lru_cache_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# Enable warnings
target_compile_options(lru_cache_lib PRIVATE
    -Wall -Wextra -Wpedantic
)

# Build the test executable
add_executable(test_lru
    tests/test_lru.cpp
)

target_link_libraries(test_lru
    lru_cache_lib
)

add_executable(test_lru_threaded
    tests/test_lru_threaded.cpp
)

target_link_libraries(test_lru_threaded
    lru_cache_lib
    Threads::Threads
)