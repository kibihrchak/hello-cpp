cmake_minimum_required(VERSION 3.16)

project (stash CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(stashTest
    ruleOfZero.cpp
    copyAndSwap.cpp
    sfinae.cpp
    perfectForwarding.cpp
    synchronization.cpp
    )


#   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   Add Conan package and link it to the main executable

include(conan.cmake)

conan_cmake_run(
    REQUIRES gtest/1.10.0
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

target_link_libraries(stashTest
    PRIVATE CONAN_PKG::gtest
)


#   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   Add GoogleTest tests

enable_testing()

include(GoogleTest)

gtest_discover_tests(stashTest)
