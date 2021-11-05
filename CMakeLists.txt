cmake_minimum_required(VERSION 3.16.0)

project(rctl VERSION 0.1.0)

find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)




add_executable(main-test tests/tests.cpp)

target_include_directories(main-test PRIVATE include)

target_link_libraries(main-test PRIVATE fmt::fmt Catch2::Catch2 Catch2::Catch2WithMain)

include(CTest)
enable_testing()
add_test(NAME all COMMAND main-test)
