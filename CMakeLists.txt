cmake_minimum_required(VERSION 3.20)

project(worker_case LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/utf-8)
endif()

add_library(worker_lib Worker.cpp Worker.h)
target_include_directories(worker_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(worker_app main.cpp)
target_link_libraries(worker_app PRIVATE worker_lib)

add_executable(worker_tests tests/WorkerTests.cpp)
target_link_libraries(worker_tests PRIVATE worker_lib)

enable_testing()
add_test(NAME worker_tests COMMAND worker_tests)
