# cmake_minimum_required(VERSION 3.14)
cmake_minimum_required(VERSION 3.0.0)
project(LINS355_unittest)

set(CMAKE_INSTALL_RPATH "/usr/local/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    test_lins355

    unit_test.cc
)

target_link_libraries(
    test_lins355

    gtest_main
    lins355_static
    serial
)

include(GoogleTest)
gtest_discover_tests(test_lins355)
