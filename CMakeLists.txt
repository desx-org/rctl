cmake_minimum_required(VERSION 3.16.0)

project(rctl VERSION 0.1.0)

find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(Doxygen)

add_executable(main-test 
  tests/test_modulo_int.cpp
  tests/test_span_array.cpp
)

target_include_directories(main-test PRIVATE include)

target_link_libraries(main-test PRIVATE fmt::fmt Catch2::Catch2 Catch2::Catch2WithMain)

target_compile_features(main-test PRIVATE cxx_std_20)

include(CTest)
enable_testing()
add_test(NAME tall COMMAND main-test)

set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
set(DOXYGEN_TAB_SIZE 2)

doxygen_add_docs(
  rctl-docs 
  include/rctl/modulo_int.hpp
  include/rctl/span_array.hpp
  ALL
  USE_STAMP_FILE
)